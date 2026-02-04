/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tracker_defs.h
 *
 * Definitions for the tracker guild.
 *
 */

#ifndef _TRACKER_H_
#define _TRACKER_H_

#define GUILD_NAME     "Tracker"
#define GUILD_TYPE     "occupational"
#define GUILD_STYLE    "ranger"

#define GUILD_TAX      30
#define GUILD_DIR      "/d/Terel/sorgum/tracker/"
#define GUILD_SHADOW   (GUILD_DIR + "tracker_shadow")
#define GUILD_SOUL     (GUILD_DIR + "tracker_soul")

#define GUILD_HELP     (GUILD_DIR + "help/")

#define GUILD_ILLEGAL_RACE ({"elf"})

#define GUILD_OBJECT (GUILD_DIR + "tracker_sash")

#define MEMBER(xx)  ((xx)->query_guild_member(GUILD_NAME))

#define BANISHED      (GUILD_DIR + "banished")

/* Tracker skills */
#define TRACKER_RANK      130600
#define TRACKER_PSIONICS  130601

#endif
