/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 15;       /* snap pixel */

/* Vanitygaps */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/* systray */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=8" };
static const char dmenufont[]       = "monospace:size=8";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#333333";
static char normfgcolor[]           = "#888888";
static char selfgcolor[]            = "#FFFFFF";
static char selbordercolor[]        = "#4C7899";
static char selbgcolor[]            = "#285577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
    //{ "notify-send Mouse$BUTTON", 1 },
    { "st -e ncmpcpp", 1},
    { "st -e htop", 2},
    { "nm-connection-editor", 3},
};

static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */

    // Program shortcuts
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    // Gaps
	{ MODKEY|SUPERKEY,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|SUPERKEY,              XK_0,      togglegaps,     {0} },
	{ MODKEY|SUPERKEY|ShiftMask,    XK_0,      defaultgaps,    {0} },

    // Layouts
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },    // Tiled Layout
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },    // bstack Layout
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[11]} },   // Centered Master
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[13]} },   // Floating
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },    // Monocle
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },

    // Navigation 
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

