-- userconf.lua -- personal luakit tweaks.
-- Auto-loaded by the system rc.lua (no need to copy the whole rc.lua).
-- Modules listed below (adblock, styles, follow/vim binds) are already
-- required by /etc/xdg/luakit/rc.lua; here we only configure them.

local settings = require "settings"

-------------------
-- Dark mode     --
-------------------
-- Dark window chrome AND makes WebKit report `prefers-color-scheme: dark`
-- to pages, so sites with native dark themes switch automatically.
settings.application.prefer_dark_mode = true

-- Force-dark for sites WITHOUT a native dark theme is handled by an optional
-- user stylesheet in the styles dir (see notes); toggle it with :styles-list.

-------------------
-- General prefs --
-------------------
settings.webview.enable_smooth_scrolling = true
settings.webview.enable_javascript       = true
settings.webview.javascript_can_open_windows_automatically = false
settings.window.home_page                = "luakit://newtab/"
settings.window.new_tab_page             = "about:blank"

-- DuckDuckGo default, with bang shortcuts. `o <term>` searches, `g <term>`
-- forces Google, etc.
settings.window.search_engines = {
    d  = "https://duckduckgo.com/?q=%s",
    g  = "https://www.google.com/search?q=%s",
    gh = "https://github.com/search?q=%s&type=repositories",
    w  = "https://en.wikipedia.org/wiki/Special:Search?search=%s",
    aw = "https://wiki.archlinux.org/index.php?search=%s",
    default = "https://duckduckgo.com/?q=%s",
}

-------------------
-- Adblock       --
-------------------
-- The adblock module is already loaded by rc.lua. It auto-loads every `*.txt`
-- filter list dropped in:  ~/.local/share/luakit/adblock/
-- Manage lists at  luakit://adblock/  or with  :adblock-* commands.
-- See download command in the post-setup notes.

-------------------
-- Follow hints  --
-------------------
-- Vimium-style letter labels instead of numbers. Home-row first for speed.
local select = require "select"
select.label_maker = function (s)
    local chars = s.charset("fjdkslaghrueiwoncpvm")
    return s.trim(s.sort(s.reverse(chars)))
end
-- follow.ignore_case is already true by default, so labels match regardless
-- of case and you can still filter elements by their visible text.

-- Give hint labels breathing room so thin glyphs (i, l, j) stay readable and
-- the text isn't jammed against the box edge. Appended last, so it wins.
local follow = require "follow"
follow.stylesheet = follow.stylesheet .. [[
#luakit_select_overlay .hint_label {
    padding: 1px 5px !important;
    min-width: 0.9em !important;
    line-height: 1.25 !important;
    text-align: center !important;
    border-radius: 3px !important;
    box-shadow: 0 1px 2px rgba(0,0,0,0.5) !important;
}
]]

-------------------
-- Colored find  --
-------------------
-- Replace WebKit's eye-burning yellow find highlight with kanagawa colors.
-- Keeps the native /, ?, n, N binds; only swaps the highlight implementation.
require "search_highlight"

-------------------
-- Extra binds   --
-------------------
-- luakit is already modal/vim-like out of the box: j/k/h/l scroll, gg/G,
-- f follow link, F open in new tab, o/t open, d close tab, u undo-close,
-- H/L (back/forward), / search, n/N next/prev. These add a few niceties.
local modes = require "modes"

modes.add_binds("normal", {
    -- Reload adblock filter lists from disk
    { "<Control-r>", "Reload page (bypass cache).",
        function (w) w:reload(true) end },
    -- Quick toggle of the force-dark user stylesheet menu
    { ",d", "Open user-styles menu (toggle dark/force-dark).",
        function (w) w:run_cmd(":styles-list") end },
    -- Copy current URL to clipboard
    { "yy", "Yank current URI to clipboard.",
        function (w)
            local uri = w.view.uri or ""
            luakit.selection.clipboard = uri
            w:notify("Yanked: " .. uri)
        end },
})

-- vim: et:sw=4:ts=8:sts=4:tw=80
