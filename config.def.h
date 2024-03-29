/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 15;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

/* Vanitygaps */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/* systray */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

/* bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* colors */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[]		    = "#000000"; /* black   */
static char termcol1[]              = "#ff0000"; /* red     */
static char termcol2[]              = "#33ff00"; /* green   */
static char termcol3[]              = "#ff0099"; /* yellow  */
static char termcol4[]              = "#0066ff"; /* blue    */
static char termcol5[]              = "#cc00ff"; /* magenta */
static char termcol6[]              = "#00ffff"; /* cyan    */
static char termcol7[]              = "#d0d0d0"; /* white   */
static char termcol8[]              = "#808080"; /* black   */
static char termcol9[]              = "#ff0000"; /* red     */
static char termcol10[]             = "#33ff00"; /* green   */
static char termcol11[]             = "#ff0099"; /* yellow  */
static char termcol12[]             = "#0066ff"; /* blue    */
static char termcol13[]             = "#cc00ff"; /* magenta */
static char termcol14[]             = "#00ffff"; /* cyan    */
static char termcol15[]             = "#ffffff"; /* white   */
static char *termcolor[] = {
	termcol0,  termcol1,  termcol2,  termcol3,  termcol4,  termcol5,
	termcol6,  termcol7,  termcol8,  termcol9,  termcol10, termcol11,
	termcol12, termcol13, termcol14, termcol15,
};
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 0;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

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
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x24", NULL };

#include "shiftview.c"
static const Key keys[] = {

	// Program shortcuts
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} },

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
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[13]} },   // Floating
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },    // Monocle
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,			XK_s,	   togglesticky,   {0} },

	// Navigation 
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
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

	{ MODKEY,                       XK_Left,      shiftview,      {.i = -1} },
    	{ MODKEY,                       XK_Right,      shiftview,      {.i = +1} },

	{ MODKEY,                       XK_n,      togglealttag,   {0} },
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
