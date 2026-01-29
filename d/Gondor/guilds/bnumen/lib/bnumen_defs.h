/*
 *	/d/Gondor/guilds/bnumen/bnumen_defs.h
 *  
 */
#ifndef BNUMEN_DEFINITIONS
#define BNUMEN_DEFINITIONS

#define BNUMEN_GUILD_MASTER "toby"

#define DEBUG(str)          find_player(BNUMEN_GUILD_MASTER)->catch_msg("[DEBUG - bnumen]: " + str + "\n")

#define GUILD_NAME          "Black Numenoreans"
#define GUILD_TYPE          "race"
#define GUILD_STYLE         "race"

#define GUILD_DIR           "/d/Gondor/guilds/bnumen/"
#define GUILD_HELP          (GUILD_DIR + "help/")
#define GUILD_NPC           (GUILD_DIR + "npc/")

#define BNUMEN_LOG          ("/d/Gondor/log/bnumen")
#define BNUMEN_MASTER       (GUILD_DIR + "rooms/join_room")
#define BNUMEN_POST         (GUILD_DIR + "post.c")
#define BNUMEN_LIBRARY      (GUILD_DIR + "rooms/lib_houses")
#define PUBLIC_LIBRARY      (GUILD_DIR + "rooms/lib_public")
#define BNUMEN_START_LOC    (GUILD_DIR + "rooms/start_room")

#define BNUMEN_SHADOW       (GUILD_DIR + "bnumen_sh")
#define BNUMEN_SOUL         (GUILD_DIR + "bnumen_soul")

#define BNUMEN_S_SUBLOC     "Black Numenoreans_s_SubLoc"

#define BNUMEN_GUILD_OBJECT "bnumen_guild_object"

#define BNUMEN_RACE         "human"

/* Different stages in titles */
#define BNUMEN_HOUSE_LEVEL  12
#define BNUMEN_LORD_LEVEL   27


/* SS_BNUMEN_LEVEL is now defined in /d/Gondor/defs.h */

/* Confirmed names in Silmarillion:
 *     Adunakhor
 *     Fuinur
 *     Gimilzor
 *     Herumor
 *     Pharazon
 *
 * Unconfirmed names:
 *     Khamul (supposedly the black rider in Shire in book I)
 *     Sakalthor
 *     Zimrathon
 */
#define BNUMEN_HOUSES		({ \
                "Adunakhor",\
                "Fuinur",\
				"Gimilzor",\
				"Herumor",\
				"Pharazon",\
				})

#define DL_SUB_LORD		99
#define DL_LORD			100
#define BNUMEN_NO_HOUSE       "none"

#define ADUNAIC_DIFF            60
#define ANCIENT_ADUNAIC_DIFF    80

#define IS_MEMBER(x)		(x->query_guild_name_race() == GUILD_NAME)

#endif
