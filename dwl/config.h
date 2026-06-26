/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const int centeredmaster_always = 1;  /* 1 means only one window is centered */
static const float rootcolor[]             = COLOR(0x1f1f28ff);
static const float bordercolor[] = COLOR(0x54546dff);
static const float focuscolor[]  = COLOR(0x7e9cd8ff);
static const float urgentcolor[] = COLOR(0xc34043ff);

static const int smartgaps                 = 1;
static const int monoclegaps               = 0;
static const unsigned int gappih           = 10;
static const unsigned int gappiv           = 10;
static const unsigned int gappoh           = 10;
static const unsigned int gappov           = 10;

/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
// static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
// static const float fullscreen_bg[] = {0.043, 0.059, 0.047, 1.0};
static const float fullscreen_bg[] = {0.122f, 0.122f, 0.157f, 1.0f};

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{ "Gimp_EXAMPLE",     NULL,       0,            1,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,           -1 }, /* Start on ONLY tag "9" */
    /* default/example rule: can be changed but cannot be eliminated; at least one rule must exist */
};

/* layout(s) */
static const Layout layouts[] = {
	{ "[]=", tile },
	{ "TTT", bstack },
	{ "===", bstackhoriz },
	{ "[M]", monocle },
	{ "><>", NULL }, /* no layout function means floating behavior */
	{ "|M|", centeredmaster },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "us,ua",
	.options = "grp:win_space_toggle,caps:escape",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.3;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
// #define MODKEY WLR_MODIFIER_ALT
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]      = { "foot", NULL };
static const char *termtmuxcmd[]  = { "foot", "tmux", NULL };
static const char *footcmd[] = { "foot", "yazi", NULL };
static const char *menucmd[] = {
    "wmenu-run",
    "-i",
    "-f", "IosevkaTermSlab Nerd Font Mono 10",
    "-N", "1f1f28ff",
    "-n", "dcd7baff",
    "-M", "2d4f67ff",
    "-m", "7e9cd8ff",
    "-S", "76946aff",
    "-s", "1f1f28ff",
    NULL
};

static const char *volupcmd[]   = { "wpctl", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *voldowncmd[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *volmutecmd[] = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };

static const char *brightupcmd[]   = { "brightnessctl", "set", "5%+", NULL };
static const char *brightdowncmd[] = { "brightnessctl", "set", "5%-", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: 2 -> at, etc. */
	/* modifier                  key                  function          argument */
	{ MODKEY,                    XKB_KEY_p,           spawn,            {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_Return,      spawn,            {.v = termcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,      spawn,            {.v = termtmuxcmd} },
  { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_e,           spawn,            {.v = footcmd} },
	/* screenshots: Print = region to clipboard; Shift+Print = region into swappy (draw/save) */
	{ 0,                         XKB_KEY_Print,       spawn,            SHCMD("grim -g \"$(slurp)\" - | wl-copy") },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_Print,       spawn,            SHCMD("grim -g \"$(slurp)\" - | swappy -f -") },
	{ MODKEY,                    XKB_KEY_b,           togglebar,        {0} },

	/* directional focus/swap with hjkl */
	{ MODKEY,                    XKB_KEY_h,           focusdir,         {.ui = 0} },  /* focus left */
	{ MODKEY,                    XKB_KEY_l,           focusdir,         {.ui = 1} },  /* focus right */
	{ MODKEY,                    XKB_KEY_k,           focusdir,         {.ui = 2} },  /* focus up */
	{ MODKEY,                    XKB_KEY_j,           focusdir,         {.ui = 3} },  /* focus down */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_h,           swapdir,          {.ui = 0} },  /* swap left */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_l,           swapdir,          {.ui = 1} },  /* swap right */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_k,           swapdir,          {.ui = 2} },  /* swap up */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_j,           swapdir,          {.ui = 3} },  /* swap down */

	{ MODKEY,                    XKB_KEY_i,           incnmaster,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,           incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_z,           zoom,             {0} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_c,           killclient,       {0} },

	/* Layouts */
	{ MODKEY, XKB_KEY_t, setlayout, {.v = &layouts[0]} },
	{ MODKEY, XKB_KEY_y, setlayout, {.v = &layouts[1]} },
	{ MODKEY, XKB_KEY_u, setlayout, {.v = &layouts[2]} },
	{ MODKEY, XKB_KEY_m, setlayout, {.v = &layouts[3]} },
	{ MODKEY, XKB_KEY_f, setlayout, {.v = &layouts[4]} },
	{ MODKEY, XKB_KEY_c, setlayout, {.v = &layouts[5]} },

	{ MODKEY,                    XKB_KEY_space,       setlayout,        {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       togglefloating,   {0} },
	{ MODKEY,                    XKB_KEY_e,           togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,       focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,      focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,        tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,     tagmon,           {.i = WLR_DIRECTION_RIGHT} },

	/* gap controls */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_g,           incgaps,       {.i = +1} },  /* increase gaps */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_s,           incgaps,       {.i = -1} },  /* decrease gaps */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_0,           togglegaps,    {0} },        /* toggle gaps */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_r,           defaultgaps,   {0} },        /* reset gaps */	

	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },

	/* hardware media keys */
	{ 0, XKB_KEY_XF86AudioRaiseVolume,  spawn, {.v = volupcmd} },
	{ 0, XKB_KEY_XF86AudioLowerVolume,  spawn, {.v = voldowncmd} },
	{ 0, XKB_KEY_XF86AudioMute,         spawn, {.v = volmutecmd} },

	{ 0, XKB_KEY_XF86MonBrightnessUp,   spawn, {.v = brightupcmd} },
	{ 0, XKB_KEY_XF86MonBrightnessDown, spawn, {.v = brightdowncmd} },

	/* fallback keys */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_equal,        spawn, {.v = volupcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_minus,        spawn, {.v = voldowncmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_0,            spawn, {.v = volmutecmd} },

	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_bracketright, spawn, {.v = brightupcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_bracketleft,  spawn, {.v = brightdowncmd} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
