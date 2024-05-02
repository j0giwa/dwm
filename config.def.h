/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx =  2;  /* border pixel of windows */
static const unsigned int snap     = 15; /* snap pixel */
static const int swallowfloating   =  0;  /* 1 means swallow floating windows by default */
static const unsigned int gappih   =  5;  /* horiz inner gap between windows */
static const unsigned int gappiv   =  5;  /* vert inner gap between windows */
static const unsigned int gappoh   = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov   = 10; /* vert outer gap between windows and screen edge */
static       int smartgaps         =  0;  /* 1 means no outer gap when there is only one window */

/* systray */
static const unsigned int systraypinning = 0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1; /* 0 means no systray */

/* bar */
static const int showbar           = 1; /* 0 means no bar */
static const int topbar            = 1;  /* 0 means bottom bar */
static const int user_bh           = 20; /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]         = { 
    "Ubuntu:style:bold:pixelsize=12:antialias=true:autohint=true", 
    "JetBrainsMono Nerd Font Mono:style:medium:pixelsize=22:antialias=true:autohint=true"
};
static const char dmenufont[]      = "Ubuntu:style:bold:size=10";

/* colors */
static char normbgcolor[]          = "#222222";
static char normbordercolor[]      = "#444444";
static char normfgcolor[]          = "#bbbbbb";
static char selfgcolor[]           = "#eeeeee";
static char selbordercolor[]       = "#005577";
static char selbgcolor[]           = "#005577";
static char termcol0[]             = "#000000";  /* black   */
static char termcol1[]             = "#ff0000";  /* red     */
static char termcol2[]             = "#33ff00";  /* green   */
static char termcol3[]             = "#ff0099";  /* yellow  */
static char termcol4[]             = "#0066ff";  /* blue    */
static char termcol5[]             = "#cc00ff";  /* magenta */
static char termcol6[]             = "#00ffff";  /* cyan    */
static char termcol7[]             = "#d0d0d0";  /* white   */
static char termcol8[]             = "#808080";  /* black   */
static char termcol9[]             = "#ff0000";  /* red     */
static char termcol10[]            = "#33ff00";  /* green   */
static char termcol11[]            = "#ff0099";  /* yellow  */
static char termcol12[]            = "#0066ff";  /* blue    */
static char termcol13[]            = "#cc00ff";  /* magenta */
static char termcol14[]            = "#00ffff";  /* cyan    */
static char termcol15[]            = "#ffffff";  /* white   */
static char *termcolor[] = {
    termcol0,  termcol1,  termcol2,  termcol3,  termcol4,  termcol5,
    termcol6,  termcol7,  termcol8,  termcol9,  termcol10, termcol11,
    termcol12, termcol13, termcol14, termcol15,
};
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbgcolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* tagging */
static const char *tags[] = {"", "", "󰒓", "󰈙", "", "󰭹", "󰝚", "󰕧", "󰏘"};
static const char ptagf[] = "%s : %s";	/* format of a tag label */
static const char etagf[] = "%s";	/* format of an empty tag */
static const int lcaselbl = 0;		/* 1 means make tag label lowercase */	
static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

/* window rules */ 
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal noswallow  monitor */
    {"Gimp", 	 NULL,     NULL,           0,         1,          0,          0,        -1},
    {"Firefox",  NULL,     NULL,           1 << 8,    0,          0,         -1,        -1},
    {"St",       NULL,     NULL,           0,         0,          1,          0,        -1},
    {NULL,       NULL,    "Event Tester",  0,         0,          0,          1,        -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"[M]", monocle},
    {"[@]", spiral},
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {":::", gaplessgrid},
    {"|M|", centeredmaster},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD,  XK_j,   ACTION##stack,  {.i = INC(+1)} }, \
    { MOD,  XK_k,   ACTION##stack,  {.i = INC(-1)} }, \
    { MOD,  XK_v,   ACTION##stack,  {.i = 0} }, \
    /* { MOD,  XK_grave,  ACTION##stack, {.i = PREVSEL}}, \ */
    /* { MOD,  XK_a,      ACTION##stack, {.i = 1}}, \ */
    /* { MOD,  XK_z,      ACTION##stack, {.i = 2}}, \ */
    /* { MOD,  XK_x,      ACTION##stack, {.i = -1}}, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor,  "-sf", selfgcolor,  NULL};
static const char *termcmd[] = {"st", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x24", NULL };

#include "shiftview.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {
    /* modifier                     key             function        argument */

    STACKKEYS(MODKEY,		    focus) 
    STACKKEYS(MODKEY|ShiftMask,     push)

    TAGKEYS(			    XK_1,	                    0)
    TAGKEYS(			    XK_2,	                    1)
    TAGKEYS(			    XK_3,	                    2)
    TAGKEYS(			    XK_4,	                    3)
    TAGKEYS(			    XK_5,	                    4)
    TAGKEYS(			    XK_6,	                    5)
    TAGKEYS(			    XK_7,	                    6)
    TAGKEYS(			    XK_8,	                    7)
    TAGKEYS(			    XK_9,	                    8)
    { MODKEY,                       XK_0,	    view,           {.ui = ~0} },
    { MODKEY|ShiftMask,             XK_0,	    tag,            {.ui = ~0} },
    { MODKEY,                       XK_comma,	    focusmon,       {.i = -1} },
    { MODKEY,                       XK_period,	    focusmon,       {.i = +1} },
    { MODKEY|ShiftMask,             XK_comma,	    tagmon,         {.i = -1} },
    { MODKEY|ShiftMask,             XK_period,	    tagmon,         {.i = +1} },
    { MODKEY,                       XK_Tab,	    view,           {0} },
    { MODKEY,                       XK_Left,	    shiftview,      {.i = -1} },
    { MODKEY,                       XK_Right,	    shiftview,      {.i = +1} },

    { MODKEY,                       XK_q,	    killclient,     {0} },
    { MODKEY|ShiftMask,		    XK_q,	    spawn,	    {.v = (const char*[]){ "sysact", NULL } } },
    { MODKEY,                       XK_Return,	    spawn,          {.v = termcmd} },
    { MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_p,           spawn,          {.v = dmenucmd} },
    { MODKEY,                       XK_w,	    spawn,          SHCMD("firefox") },
    { MODKEY,                       XK_e,	    spawn,          SHCMD("st -e lf") },
    { MODKEY|ShiftMask,             XK_e,	    spawn,          SHCMD("emacs") },

    { MODKEY,                       XK_t,	    setlayout,      {.v = &layouts[0]} },  /* tile */
    { MODKEY|ShiftMask,             XK_t,	    setlayout,      {.v = &layouts[5]} },  /* bstack */
    { MODKEY,                       XK_z,	    setlayout,      {.v = &layouts[2]} },  /* spiral */
    { MODKEY|ShiftMask,             XK_z,	    setlayout,      {.v = &layouts[3]} },  /* dwindle */
    { MODKEY,                       XK_m,	    setlayout,      {.v = &layouts[1]} },  /* deck */
    { MODKEY|ShiftMask,             XK_m,	    setlayout,      {.v = &layouts[4]} },  /* monocle */
    { MODKEY,                       XK_u,	    setlayout,      {.v = &layouts[11]} }, /* centeredmaster */
    { MODKEY|ShiftMask,             XK_u,	    setlayout,      {.v = &layouts[12]} }, /* centeredfloatingmaster */
    { MODKEY,                       XK_f,           fullscreen,     {0} },                 /* Fullscreen */ 
    { MODKEY|ShiftMask,             XK_f,	    setlayout,      {.v = &layouts[13]} }, /* Floating */

    { MODKEY|ShiftMask,             XK_g,           defaultgaps,    {0} },
    { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                       XK_g,           togglegaps,     {0} },
    { MODKEY,                       XK_y,           incrgaps,       {.i = +3 } },
    { MODKEY,                       XK_x,           incrgaps,       {.i = -3 } },
    
    { MODKEY,                       XK_i,           incnmaster,     {.i = +1} },
    { MODKEY,                       XK_d,           incnmaster,     {.i = -1} },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_space,       zoom,           {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
    { MODKEY,                       XK_s,           togglesticky,   {0} },

    { MODKEY,                       XK_F3,	    spawn,	    {.v = (const char*[]){ "displayselect", NULL } } },
    { MODKEY,                       XK_F4,	    spawn,	    SHCMD("st -e pulsemixer") },
    { MODKEY,                       XK_F5,	    xrdb,           {.v = NULL} },
    { MODKEY,                       XK_F11,	    spawn,	    SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { MODKEY,                       XK_F12,	    spawn,	    SHCMD("remaps") },
    { MODKEY,                       XK_Insert,	    spawn,	    SHCMD("xdotool type $(grep -v '^#' ~/.local/share/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },

    { MODKEY,                       XK_Page_Up,     shiftview,      { .i = -1 } },
    { MODKEY|ShiftMask,             XK_Page_Up,     shifttag,       { .i = -1 } },
    { MODKEY,                       XK_Page_Down,   shiftview,      { .i = +1 } },
    { MODKEY|ShiftMask,             XK_Page_Down,   shifttag,       { .i = +1 } },
    
    { 0,                            XF86XK_AudioMute,         spawn, SHCMD("set-sink-mute @DEFAULT_SINK@ toggle") },
    { 0,                            XF86XK_AudioLowerVolume,  spawn, SHCMD("set-sink-volume @DEFAULT_SINK@ -10%") },
    { 0,                            XF86XK_AudioRaiseVolume,  spawn, SHCMD("set-sink-volume @DEFAULT_SINK@ +10%") },
    { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-") },
    { 0,                            XF86XK_MonBrightnessUp,   spawn, SHCMD("brightnessctl set 10%+") },

    /* { MODKEY|Mod4Mask,              XK_h,	    incrgaps,       {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_l,	    incrgaps,       {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_h,	    incrogaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_l,	    incrogaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_h,	    incrigaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_l,	    incrigaps,      {.i = -1 } }, */
    /* { MODKEY,                       XK_y,	    incrihgaps,     {.i = +1 } }, */
    /* { MODKEY,                       XK_o,	    incrihgaps,     {.i = -1 } }, */
    /* { MODKEY|ControlMask,           XK_y,	    incrivgaps,     {.i = +1 } }, */
    /* { MODKEY|ControlMask,           XK_o,	    incrivgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_y,	    incrohgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_o,	    incrohgaps,     {.i = -1 } }, */
    /* { MODKEY|ShiftMask,             XK_y,	    incrovgaps,     {.i = +1 } }, */
    /* { MODKEY|ShiftMask,             XK_o,	    incrovgaps,     {.i = -1 } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0}},
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]}},
    { ClkWinTitle,          0,              Button2,        zoom,           {0}},
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd}},
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0}},
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0}},
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0}},
    { ClkTagBar,            0,              Button1,        view,           {0}},
    { ClkTagBar,            0,              Button3,        toggleview,     {0}},
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0}},
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0}},
};

