--- Kanagawa-colored in-page find.
--
-- WebKitGTK's native find highlight is a fixed, eye-searing yellow that luakit
-- 2.4.0 does not expose. This module keeps the native search UX (the `/`, `?`,
-- `n`, `N` binds and the input bar) but swaps the *implementation*: instead of
-- calling WebKit's find controller, it drives a small JS highlighter via the
-- CSS Custom Highlight API, colored with the kanagawa palette.
--
-- All matches: waveBlue2 bg / fujiWhite fg. Current match: carpYellow bg /
-- sumiInk0 fg (dark text, readable). No DOM mutation -> safe on complex pages.

local webview = require "webview"

local _M = {}

-- The injected highlighter. Idempotent: re-running only (re)defines the API.
local find_js = [==[
(function () {
    if (window.__lkfind) return "ready";
    if (!(window.CSS && CSS.highlights && window.Highlight)) {
        window.__lkfind = { unsupported: true,
            search: function () { return -1; },
            next: function () { return -1; }, prev: function () { return -1; },
            clear: function () {} };
        return "unsupported";
    }
    var ranges = [], idx = -1;

    if (!document.getElementById("__lkfind_style")) {
        var st = document.createElement("style");
        st.id = "__lkfind_style";
        st.textContent =
            "::highlight(lkfind){background-color:#2D4F67;color:#DCD7BA;}" +
            "::highlight(lkfind-current){background-color:#E6C384;color:#16161D;}";
        (document.head || document.documentElement).appendChild(st);
    }

    function clearH() {
        CSS.highlights.delete("lkfind");
        CSS.highlights.delete("lkfind-current");
        ranges = []; idx = -1;
    }
    function paint() {
        var all = new Highlight();
        for (var i = 0; i < ranges.length; i++) all.add(ranges[i]);
        CSS.highlights.set("lkfind", all);
        if (idx >= 0 && ranges[idx]) {
            var cur = new Highlight(); cur.add(ranges[idx]);
            CSS.highlights.set("lkfind-current", cur);
        } else CSS.highlights.delete("lkfind-current");
    }
    function scrollTo() {
        var r = ranges[idx]; if (!r) return;
        var el = r.startContainer.parentElement;
        if (el && el.scrollIntoView) el.scrollIntoView({ block: "center", inline: "nearest" });
    }
    function build(q) {
        clearH();
        if (!q) return 0;
        var ql = q.toLowerCase(), root = document.body || document.documentElement;
        var walker = document.createTreeWalker(root, NodeFilter.SHOW_TEXT, {
            acceptNode: function (n) {
                if (!n.nodeValue || !n.nodeValue.trim()) return NodeFilter.FILTER_REJECT;
                var p = n.parentElement; if (!p) return NodeFilter.FILTER_REJECT;
                var t = p.tagName;
                if (t === "SCRIPT" || t === "STYLE" || t === "NOSCRIPT") return NodeFilter.FILTER_REJECT;
                return NodeFilter.FILTER_ACCEPT;
            }
        });
        var node;
        while ((node = walker.nextNode())) {
            var low = node.nodeValue.toLowerCase(), from = 0, i;
            while ((i = low.indexOf(ql, from)) !== -1) {
                var r = document.createRange();
                r.setStart(node, i); r.setEnd(node, i + q.length);
                ranges.push(r); from = i + q.length;
            }
        }
        return ranges.length;
    }
    function go(fwd) {
        if (!ranges.length) return 0;
        idx = fwd ? (idx + 1) % ranges.length : (idx - 1 + ranges.length) % ranges.length;
        paint(); scrollTo();
        return idx + 1;
    }
    window.__lkfind = {
        search: function (q) {
            var n = build(q);
            idx = n ? 0 : -1;
            paint(); scrollTo();
            return n;
        },
        next: function () { return go(true); },
        prev: function () { return go(false); },
        clear: clearH
    };
    return "ready";
})();
]==]

-- Encode a Lua string as a JS double-quoted string literal.
local function js_str(s)
    return '"' .. s:gsub('[\\"\n\r\t]', {
        ["\\"] = "\\\\", ['"'] = '\\"',
        ["\n"] = "\\n", ["\r"] = "\\r", ["\t"] = "\\t",
    }) .. '"'
end

local function run(view, expr, cb)
    view:eval_js(find_js .. "\n;" .. expr, { callback = cb })
end

-- Override the webview search methods registered by lib/search.lua.
webview.methods.search = function (view, w, text, forward, wrap)
    if forward == nil then forward = true end
    w.search_state = w.search_state or { by_view = setmetatable({}, { __mode = "k" }) }
    local s = w.search_state
    -- Keep native n/N bind code (which reads .ret) from indexing nil.
    s.by_view[view] = s.by_view[view] or { ret = true }

    -- nil text == repeat/navigate (n / N).
    if text == nil then
        if not s.last_search or s.last_search == "" then return end
        run(view, "window.__lkfind." .. (forward and "next" or "prev") .. "()",
            function (n)
                s.by_view[view].ret = (tonumber(n) or 0) ~= 0
                w:set_ibar_theme(s.by_view[view].ret and nil or "error")
            end)
        return
    end

    if text == "" then return w:clear_search() end

    s.last_search = text
    s.searched = true
    run(view, "window.__lkfind.search(" .. js_str(text) .. ")", function (n)
        n = tonumber(n) or 0
        if n == -1 then
            w:warning("colored find unavailable (no CSS Custom Highlight API)")
            return
        end
        s.by_view[view].ret = n ~= 0
        w:set_ibar_theme(n ~= 0 and nil or "error")
    end)
end

webview.methods.clear_search = function (view, w, clear_state)
    w:set_ibar_theme()
    run(view, "window.__lkfind && window.__lkfind.clear()")
    if clear_state ~= false then
        w.search_state = { by_view = setmetatable({}, { __mode = "k" }) }
    else
        w.search_state.searched = false
        w.search_state.last_search = nil
    end
end

return _M

-- vim: et:sw=4:ts=8:sts=4:tw=80
