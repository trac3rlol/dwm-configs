/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappx = 6;    /* pixel gap between clients */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const int horizpadbar = 6;       /* horizontal padding for statusbar */
static const int vertpadbar = 7;        /* vertical padding for statusbar */
static const char *fonts[] = {"JetBrains Mono:size=12",
                              "SymbolsNerdFont:size=16",
                              "Hack:size=12:antialias=true:autohint=true",
                              "fontawesome:size=10",
                              "NotoColorEmoji:size=12",
                              "JoyPixels:size=12:antialias=true:autohint=true"};
static const char col_1[] = "#000000"; /* background color of bar */
static const char col_2[] = "#444444"; /* border color unfocused windows */
static const char col_3[] = "#d7d7d7";
static const char col_4[] =
    "#bb83f7"; /* border color focused windows and tags */
/* bar opacity
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_3, col_1, col_2},
    [SchemeSel] = {col_3, col_4, col_4},
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"", "", "", "", "嗢", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Brave-browser", NULL, NULL, 1 << 1, 0, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"HHH", grid}, {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN, KEY, TAG)                                               \
  {MODKEY, CHAIN, KEY, view, {.ui = 1 << TAG}},                                \
      {MODKEY | ControlMask, CHAIN, KEY, toggleview, {.ui = 1 << TAG}},        \
      {MODKEY | ShiftMask, CHAIN, KEY, tag, {.ui = 1 << TAG}},                 \
      {MODKEY | ControlMask | ShiftMask,                                       \
       CHAIN,                                                                  \
       KEY,                                                                    \
       toggletag,                                                              \
       {.ui = 1 << TAG}},
#define CMD(cmd)                                                               \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* dmenu */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[] = {"dmenu_run", "-c", "-g",    "1", "-l",
                                 "25",        "-p", "Run: ", NULL};
static const char *termcmd[] = {"kitty", NULL};

static Key keys[] = {
    /* modifier             chain key  key        function        argument */
    {MODKEY | ShiftMask, -1, XK_Return, spawn, {.v = dmenucmd}},
    {MODKEY, -1, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | Mod1Mask, -1, XK_b, togglebar, {0}},
    {MODKEY | ShiftMask, -1, XK_j, rotatestack, {.i = +1}},
    {MODKEY | ShiftMask, -1, XK_k, rotatestack, {.i = -1}},
    {MODKEY, -1, XK_j, focusstack, {.i = +1}},
    {MODKEY, -1, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, -1, XK_Up, incnmaster, {.i = +1}},
    {MODKEY | ShiftMask, -1, XK_Down, incnmaster, {.i = -1}},
    {MODKEY, -1, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, -1, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ControlMask, -1, XK_Return, zoom, {0}},
    {MODKEY, -1, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, -1, XK_c, killclient, {0}},

    /* Layout manipulation */
    {MODKEY, -1, XK_Tab, cyclelayout, {.i = -1}},
    {MODKEY | ShiftMask, -1, XK_Tab, cyclelayout, {.i = +1}},
    {MODKEY, -1, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, -1, XK_space, togglefloating, {0}},

    /* Switch to specific layouts */
    {MODKEY, -1, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, -1, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, -1, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, -1, XK_g, setlayout, {.v = &layouts[3]}},

    {MODKEY, -1, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, -1, XK_0, tag, {.ui = ~0}},

    /* Switching between monitors */
    {MODKEY, -1, XK_comma, focusmon, {.i = -1}},
    {MODKEY, -1, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, -1, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, -1, XK_period, tagmon, {.i = +1}},

    /* Favorite programs */
    {MODKEY, -1, XK_b, spawn, CMD("brave")},
    {MODKEY | Mod1Mask, -1, XK_f, spawn, CMD("pcmanfm")},
    {MODKEY, -1, XK_F7, spawn, CMD("virt-manager")},
    {MODKEY, -1, XK_x, spawn, CMD("$HOME/.config/dmenu/scripts/powermenu.sh")},

    TAGKEYS(-1, XK_1, 0) TAGKEYS(-1, XK_2, 1) TAGKEYS(-1, XK_3, 2)
        TAGKEYS(-1, XK_4, 3) TAGKEYS(-1, XK_5, 4) TAGKEYS(-1, XK_6, 5)
            TAGKEYS(-1, XK_7, 6) TAGKEYS(-1, XK_8, 7)
                TAGKEYS(-1, XK_9, 8){MODKEY | ShiftMask, -1, XK_q, quit, {0}},
    {MODKEY | ShiftMask, -1, XK_r, quit, {1}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click           event mask   button          function        argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
