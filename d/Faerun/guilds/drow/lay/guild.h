/*
 * drow/lay/guild.h
 *
 * This is the master defines file for the drow layman guild.
 */
#ifndef __DROW_LAYMAN_GUILD__
#define __DROW_LAYMAN_GUILD__

#include "../drow.h"

/* General guild defines. */
#define GUILD_TAX       13
#define GUILD_TYPE      "layman"
#define GUILD_STYLE     "fighter"
#define GUILD_NAME      DROW_L_GUILD
#define GUILD_SOUL      (P_DROW_LAYMAN + "soul")
#define GUILD_SHADOW    (P_DROW_LAYMAN + "shadow")
#define GUILD_OBJECT    (P_DROW_LAYMAN + "object")
#define GUILD_LOGS      (P_DROW_LAYMAN + "logs/")
#define GUILD_HELP      (P_DROW_LAYMAN + "help/")
#define GSERVER         DROW_L_SERVER
#define GOBJECT_NAME    DROW_L_OBJECT

/* Our default logfile settings. */
#define BANLOG          (GUILD_LOGS + "general")
#define JOINLOG         (GUILD_LOGS + "general")
#define LEFTLOG         (GUILD_LOGS + "general")

/* This uses Faerun custom time2format function. */
#define GLOG(log, msg)  write_log((log), \
    time2format(time(), "mm-dd-yyyy tt: ") + (msg) +"\n", 250000, 10)

/* Indices into the members array of the server. */
#define M_TITLE     0
#define M_OPTIONS   1
#define M_ACTIVE    2

/* The selectable Drow titles. */
#define DROW_TITLES ({ \
    "assassin",        \
    "avenger",         \
    "battlemaster",    \
    "battlemistress",  \
    "child",           \
    "daughter",        \
    "death",           \
    "defender",        \
    "despoiler",       \
    "emissary",        \
    "hunter",          \
    "huntress",        \
    "pathfinder",      \
    "punisher",        \
    "raider",          \
    "scourge",         \
    "scout",           \
    "son",             \
    "terror",          \
    "vengeance",       \
})

/* This is to prevent wrong-gendered titles. */
#define DROW_TITLES_SUB ([ \
    "son": ({ "son", "daughter" }),                             \
    "daugther": ({ "son", "daughter" }),                        \
    "hunter": ({ "hunter", "huntress" }),                       \
    "huntress": ({ "hunter", "huntress" }),                     \
    "battlemaster": ({ "battlemaster", "battlemistress" }),     \
    "battlemistress": ({ "battlemaster", "battlemistress" }),   \
])

#define DROW_TITLES_PRE ({ \
    "", "Favoured", "Highly Favoured",                          \
})

#define DROW_TITLES_POST ({ \
    "of the Night Below",                                       \
    "from the Night Below",                                     \
})

#endif  __DROW_LAYMAN_GUILD__
