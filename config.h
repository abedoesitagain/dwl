/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1.5;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"Fira Code:size=10"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static int enableautoswallow = 1; /* enables autoswallowing newly spawned clients */
static float swallowborder = 1.0f; /* add this multiplied by borderpx to border when a client is swallowed */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xffffffff, 0x181818ff, 0x333333ff },
  /*[SchemeSel]  = { 0xd8d8d8ff, 0x005577ff, 0x005577ff },*/
    [SchemeSel]  = { 0x181818ff, 0x90a959ff, 0x90a959ff },
	[SchemeUrg]  = { 0,          0,          0x770000ff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* Autostart */
static const char *const autostart[] = {
        "gentoo-pipewire-launcher", "restart", NULL,
        "wbg", "-s", "/home/abe/pics/wp", NULL,
        "kdeconnectd", NULL,
        "playerctld", NULL,
        "foot", "--server", NULL,
        "darkman", "run", NULL,
        NULL /* terminate */
};


static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   isterm   noswallow   monitor */
	{ "foot",             NULL,       0,            0,           1,       1,          -1 },
	{ "footclient",       NULL,       0,            0,           1,       1,          -1 },
	{ "st",               NULL,       0,            0,           1,       1,          -1 },
	{ "Gimp_EXAMPLE",     NULL,       0,            1,           0,       0,          -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,           0,       0,          -1 }, /* Start on ONLY tag "9" */
    /* default/example rule: can be changed but cannot be eliminated; at least one rule must exist */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const struct xkb_rule_names xkb_rules[] = {
	{
		/* can specify fields: rules, model, layout, variant, options */
		.layout = "us",
		.options = "caps:escape",
	},
	{
		.layout = "ara",
		.options = "caps:escape",
	},
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 0;
static const int natural_scrolling = 1;
static const int disable_while_typing = 0;
static const int left_handed = 0;
static const int middle_button_emulation = 1;
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
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

static const int cursor_timeout = 1;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "footclient", NULL };
static const char *trcmd[] = { "footclient", "-e", "tremc", "--skip-version-check", NULL };
static const char *fmcmd[] = { "footclient", "-e", "lf", NULL };
static const char *lockcmd[] = { "lock", NULL };
static const char *menucmd[] = { "wmenu-run", NULL };
static const char *volupcmd[] = { "wpctl", "set-volume", "@DEFAULT_SINK@", "10%+", NULL };
static const char *voldncmd[] = { "wpctl", "set-volume", "@DEFAULT_SINK@", "10%-", NULL };
static const char *mutecmd[] = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *brtupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brtdncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *brwsrcmd[] = { "librewolf", NULL };
static const char *pamxcmd[] = { "footclient", "-e", "pulsemixer", NULL };
static const char *topcmd[] = { "footclient", "-e", "btop", NULL };
static const char *scrnshtcmd[] = { "scrnsht", NULL };
static const char *scrnshtgcmd[] = { "scrnsht-g", NULL };
static const char *playpausecmd[] = { "playerctl", "play-pause", NULL };
static const char *nextcmd[] = { "playerctl", "next", NULL };
static const char *prevcmd[] = { "playerctl", "previous", NULL };
static const char *btcmd[] = { "btmenu", "Bluetooth", NULL };
static const char *wfcmd[] = { "nmenu", NULL };
static const char *calccmd[] = { "galculator", NULL };
static const char *opencmd[] = { "open.sh", NULL };
static const char *connectcmd[] = { "connectmenu", NULL };
static const char *darktheme[] = { "darkman", "toggle", NULL };
static const char *opentodo[] = { "footclient", "nvim", "/home/abe/docs/todo.md",NULL };
static const char *rsscmd[] = { "footclient", "newsboat", NULL };
static const char *reeecmd[] = { "reee", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_r,          spawn,          {.v = reeecmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_N,          spawn,          {.v = rsscmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          spawn,          {.v = pamxcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     spawn,          {.v = fmcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,          spawn,          {.v = trcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_B,          spawn,          {.v = topcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_L,          spawn,          {.v = lockcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,          spawn,          {.v = darktheme} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_i,          spawn,          {.v = opentodo} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_S,          spawn,          {.v = scrnshtcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT|WLR_MODIFIER_CTRL, XKB_KEY_S,          spawn,          {.v = scrnshtgcmd} },
	{ MODKEY,                    XKB_KEY_w,          spawn,          {.v = brwsrcmd} },
	{ MODKEY,                    XKB_KEY_i,          spawn,          {.v = wfcmd} },
	{ MODKEY,                    XKB_KEY_u,          spawn,          {.v = btcmd} },
	{ MODKEY,                    XKB_KEY_s,          spawn,          {.v = playpausecmd} },
	{ 0,                         XKB_KEY_XF86AudioPlay, spawn,     	 {.v = playpausecmd} },
	{ 0,                         XKB_KEY_XF86AudioNEXT, spawn,     	 {.v = nextcmd} },
	{ 0,                         XKB_KEY_XF86AudioPREV, spawn,     	 {.v = previouscmd} },
	{ MODKEY,                    XKB_KEY_o,          spawn,          {.v = opencmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_o,          spawn,          {.v = connectcmd} },
	{ 0,                         XKB_KEY_XF86Calculator, spawn,    	 {.v = calccmd} },
	{ MODKEY,                    XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_space,      switchxkbrule,  {0} },
	{ WLR_MODIFIER_SHIFT|WLR_MODIFIER_CTRL, XKB_KEY_K,    spawn,     {.v = volupcmd} },
	{ WLR_MODIFIER_SHIFT|WLR_MODIFIER_CTRL, XKB_KEY_J,    spawn,     {.v = voldncmd} },
	{ 0,                    XKB_KEY_XF86AudioRaiseVolume, spawn,     {.v = volupcmd} },
	{ 0,                    XKB_KEY_XF86AudioLowerVolume, spawn,     {.v = voldncmd} },
	{ 0,                    XKB_KEY_XF86AudioMute,        spawn,     {.v = mutecmd} },
	{ WLR_MODIFIER_SHIFT|WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_K,          spawn,     	 {.v = brtupcmd} },
	{ 0,                    XKB_KEY_XF86MonBrightnessUp, spawn,     	 {.v = brtupcmd} },
	{ WLR_MODIFIER_SHIFT|WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_J,          spawn,     	 {.v = brtdncmd} },
	{ 0,                    XKB_KEY_XF86MonBrightnessDown, spawn,     	 {.v = brtdncmd} },
/*	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
        { MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },*/
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_Tab,        zoom,           {0} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_c,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
/*      { MODKEY,                    XKB_KEY_space,      setlayout,      {0} },*/
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,         togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

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
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
