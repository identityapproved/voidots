-------------------------------
-- Kanagawa luakit theme      --
-- palette: github.com/rebelot/kanagawa.nvim
-------------------------------

local theme = {}

-- Kanagawa "wave" palette
local sumiInk0   = "#16161D"
local sumiInk1   = "#181820"
local sumiInk2   = "#1a1a22"
local sumiInk3   = "#1F1F28"
local sumiInk4   = "#2A2A37"
local fujiWhite  = "#DCD7BA"
local oldWhite   = "#C8C093"
local fujiGray   = "#727169"
local waveBlue1  = "#223249"
local waveBlue2  = "#2D4F67"
local crystalBlue= "#7E9CD8"
local springBlue = "#7FB4CA"
local springGreen= "#98BB6C"
local autumnGreen= "#76946A"
local carpYellow = "#E6C384"
local roninYellow= "#FF9E3B"
local sakuraPink = "#D27E99"
local waveRed    = "#E46876"
local peachRed   = "#FF5D62"
local oniViolet  = "#957FB8"
local dragonBlue = "#658594"

-- Default settings
theme.font = '14px "IosevkaTermSlab Nerd Font", monospace'
theme.fg   = fujiWhite
theme.bg   = sumiInk3

-- General colours
theme.success_fg = springGreen
theme.loaded_fg  = crystalBlue
theme.error_fg = fujiWhite
theme.error_bg = peachRed

-- Warning colours
theme.warning_fg = peachRed
theme.warning_bg = sumiInk1

-- Notification colours
theme.notif_fg = fujiWhite
theme.notif_bg = sumiInk1

-- Menu colours
theme.menu_fg                   = fujiWhite
theme.menu_bg                   = sumiInk2
theme.menu_selected_fg          = sumiInk0
theme.menu_selected_bg          = carpYellow
theme.menu_title_bg             = sumiInk2
theme.menu_primary_title_fg     = sakuraPink
theme.menu_secondary_title_fg   = fujiGray

theme.menu_disabled_fg = fujiGray
theme.menu_disabled_bg = theme.menu_bg
theme.menu_enabled_fg = theme.menu_fg
theme.menu_enabled_bg = theme.menu_bg
theme.menu_active_fg = springGreen
theme.menu_active_bg = theme.menu_bg

-- Proxy manager
theme.proxy_active_menu_fg      = fujiWhite
theme.proxy_active_menu_bg      = sumiInk2
theme.proxy_inactive_menu_fg    = fujiGray
theme.proxy_inactive_menu_bg    = sumiInk2

-- Statusbar specific
theme.sbar_fg         = fujiWhite
theme.sbar_bg         = sumiInk0

-- Downloadbar specific
theme.dbar_fg         = fujiWhite
theme.dbar_bg         = sumiInk0
theme.dbar_error_fg   = peachRed

-- Input bar specific
theme.ibar_fg           = fujiWhite
theme.ibar_bg           = sumiInk1

-- Tab label
theme.tab_fg            = fujiGray
theme.tab_bg            = sumiInk1
theme.tab_hover_bg      = sumiInk4
theme.tab_ntheme        = oldWhite
theme.selected_fg       = fujiWhite
theme.selected_bg       = sumiInk3
theme.selected_ntheme   = carpYellow
theme.loading_fg        = crystalBlue
theme.loading_bg        = sumiInk1

theme.selected_private_tab_bg = waveBlue2
theme.private_tab_bg    = waveBlue1

-- Trusted/untrusted ssl colours
theme.trust_fg          = springGreen
theme.notrust_fg        = peachRed

-- Follow mode hints
theme.hint_font = '15px bold "IosevkaTermSlab Nerd Font", monospace'
theme.hint_fg = sumiInk0
theme.hint_bg = carpYellow
theme.hint_border = "1px solid " .. sumiInk0
theme.hint_opacity = "1.0"
theme.hint_overlay_bg = "rgba(126,156,216,0.25)"
theme.hint_overlay_border = "1px dotted " .. crystalBlue
theme.hint_overlay_selected_bg = "rgba(152,187,108,0.30)"
theme.hint_overlay_selected_border = "1px dotted " .. springGreen

-- General colour pairings
theme.ok = { fg = fujiWhite, bg = sumiInk1 }
theme.warn = { fg = peachRed, bg = sumiInk1 }
theme.error = { fg = fujiWhite, bg = peachRed }

-- Gopher page style
theme.gopher_light = { bg = oldWhite, fg = sumiInk0, link = waveBlue2 }
theme.gopher_dark  = { bg = sumiInk3, fg = fujiWhite, link = roninYellow }

return theme

-- vim: et:sw=4:ts=8:sts=4:tw=80
