/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Proggy Vector Dotted:size=6" };

static const char fg_light[]          = "#000000";
static const char bg_light[]          = "#ffffff";
static const char bor_light[]         = "#595959";
static const char bor_sel_light[]     = "#595959";

static const char fg_dark[]          = "#ffffff";
static const char bg_dark[]          = "#000000";
static const char bor_dark[]         = "#595959";
static const char bor_sel_dark[]     = "#595959";

static const char *colors[][3]      = {
    //              fg     bg     bor
    // [SchemeNorm]
    // [SchemeSel]
	{fg_light,    bg_light,    bor_light},      // SchemeNorm light
	{bg_light,    fg_light,    bor_sel_light},  // SchemeSel  light
    {fg_dark,     bg_dark,     bor_dark},       // SchemeNorm dark
	{bg_dark,     fg_dark,     bor_sel_dark},   // SchemeSel  dark
};

/* tagging */
static const char *tags[] = { "nil", "edit", "www", "com", "misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title                      tags mask     isfloating   monitor */
	{ NULL,       NULL,       "GNU Image",               1 << 1,            0,           -1 },
	{ NULL,       NULL,       "Mozilla Firefox",         1 << 2,            0,           -1 },
    { NULL,       NULL,       "GNU Emacs",               1 << 1,            0,           -1 },
    { NULL,       NULL,       "LibreOffice",             1 << 1,            0,           -1 },
    { NULL,       NULL,       "NVIDIA Settings",         1 << 1,            0,           -1 },
    { NULL,       NULL,       "Audacity",                1 << 1,            0,           -1 },
    { NULL,       NULL,       "st",                      0,                 0,           -1 },
    { NULL,       NULL,       "Volume Control",          0,                 0,           -1 },
    { NULL,       NULL,       "Steam",                   1 << 4,            0,           -1 },
    { NULL,       NULL,       "Minecraft Launcher",      1 << 4,            0,           -1 },
    { NULL,       NULL,       "Lutris",                  1 << 4,            0,           -1 }
    // email/chat/irc client on tag #4(1 << 3)
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "&",      dwindle},
	{ "-",      tile },    /* first entry is default */
	{ "*",      NULL },    /* no layout function means floating behavior */
	{ ".",      monocle },
	{ "@",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|Mod1Mask,  KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static const char *bemenu_cmd[] = { "/bin/sh", "-c", "\
LD_LIBRARY_PATH=/home/lucas/programming/foss/bemenu BEMENU_RENDERERS=/home/lucas/programming/foss/bemenu \
/home/lucas/programming/foss/bemenu/bemenu-run -p bemenu \
--fn \"Proggy Vector Dotted 12\" \
--border 2 --prefix -- --margin 100 \
--center --fixed-height --counter always --list \"10 up\" \
--single-instance \
--tb \"#000000\" --tf \"#ffffff\" \
--fb \"#ffffff\" --ff \"#000000\" \
--nb \"#ffffff\" --nf \"#000000\" \
--hb \"#ffffff\" --hf \"##005e8b\" \
--fbb \"#ffffff\" --fbf \"#000000\" \
--sb \"#ffffff\" --sf \"#000000\" \
--ab \"#ffffff\" --af \"#000000\" \
--scb \"#ffffff\" --scf \"#000000\" \
--bdr \"#000000\"",
                                    NULL };
static const char *toggle_theme_cmd[] = { "/bin/sh", "-c", "/usr/bin/theme_toggle", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_space,  spawn,          {.v = bemenu_cmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_c,      spawn,          {.v = toggle_theme_cmd } },
    { MODKEY,                       XK_c,      toggletheme,    {0} },
	{ MODKEY,                       XK_y,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_r,      reorganizetags, {0} },
	{ MODKEY|Mod1Mask,              XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_6,      view,           {.ui = ~0 } },
	{ MODKEY|Mod1Mask,              XK_6,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_bracketleft,            1)
	TAGKEYS(                        XK_braceleft,              2)
	TAGKEYS(                        XK_braceright,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_equal,                  5)
	{ MODKEY|Mod1Mask,              XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

