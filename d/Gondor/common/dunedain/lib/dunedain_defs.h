/*
 *	/d/Gondor/common/dunedain/dunedain_defs.h
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Coded by Olorin.
 */
#ifndef DUNEDAIN_DEFINITIONS
#define DUNEDAIN_DEFINITIONS

#define GUILD_NAME		"Dunedain"
#define GUILD_TYPE		"race"
#define GUILD_STYLE		"race"

#define GUILD_DIR		"/d/Gondor/common/dunedain/"
#define GUILD_HELP		(GUILD_DIR + "help/")

#define DUNEDAIN_LOG		("/d/Gondor/log/dunedain")
#define DUNEDAIN_MASTER		(GUILD_DIR + "join_room")
#define DUNEDAIN_POST		(GUILD_DIR + "post.c")
#define DUNEDAIN_LIBRARY	(GUILD_DIR + "rooms/lib_houses")
#define PUBLIC_LIBRARY	(GUILD_DIR + "rooms/lib_public")
#define DUNEDAIN_START_LOC	(GUILD_DIR + "rooms/start_room")

#define DUNEDAIN_SHADOW		(GUILD_DIR + "dunedain_sh")
#define DUNEDAIN_SOUL		(GUILD_DIR + "dunedain_soul")

#define DUNEDAIN_S_SUBLOC	"Dunedain_s_SubLoc"

#define DUNEDAIN_GUILD_OBJECT	"dunedain_guild_object"

#define DUNEDAIN_RACE		"human"

/* SS_DUNEDAIN_LEVEL is now defined in /d/Gondor/defs.h */

#define DUNEDAIN_HOUSES2	({ "Beor", })

#define DUNEDAIN_HOUSES		({ \
				"Beor",\
				"Haladin",\
				"Hador",\
				"Thalion",\
				"Hurin",\
				"Aranarth",\
				"Amandil",\
				"Belecthor",\
				"Borlad",\
				"Hallacar",\
				"Agarwaen",\
				"Umarth",\
				})

#define DL_SUB_LORD		99
#define DL_LORD			100
#define DUNEDAIN_NO_HOUSE       "none"

#define DUNEDAIN_I_SONG_VERSE	"dunedain_i_song_verse"
#define DUNEDAIN_S_SINGING	"dunedain_s_singing"
#define ADUNAIC_DIFF    60

#define IS_MEMBER(x)		(x->query_guild_name_race() == GUILD_NAME)

#endif
