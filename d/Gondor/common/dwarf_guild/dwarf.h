/*
 * /d/Gondor/common/dwarf_guild/dwarf.h
 *
 * Some definitions for the dwarven race guild
 *
 * /Mercade, 3 November 1993
 *
 * Revision history:
 */

#ifndef DWARVEN_RACE_GUILD_DEFINITIONS
#define DWARVEN_RACE_GUILD_DEFINITIONS

#include "/d/Gondor/defs.h"

/* Directories. */
#define DWARVEN_RACE_GUILD_HELP    (DWARF_DIR + "help/")
#define DWARVEN_RACE_GUILD_TEXT    (DWARF_DIR + "text/")
#define DWARVEN_RACE_GUILD_NPCS    (DWARF_DIR + "npc/")
#define DWARVEN_RACE_GUILD_BEARS   (DWARF_DIR + "bear/")
#define DWARVEN_RACE_GUILD_OBJECTS (DWARF_DIR + "obj/")
#define DWARVEN_RACE_GUILD_ARMOURS (DWARF_DIR + "arm/")
#define DWARVEN_RACE_GUILD_WEAPONS (DWARF_DIR + "wep/")

/* Shadow and soul. */
#define DWARVEN_RACE_GUILD_SHADOW  (DWARF_DIR + "dwarf_shadow")
#define DWARVEN_RACE_GUILD_SOUL    (DWARF_DIR + "dwarf_soul")

/* The guild object for members */
#define DWARVEN_RACE_GUILD_BELT    (DWARF_DIR + "belt")

#define DWARVEN_RACE_GUILD_PREFIX  ("_dwarven_race_guild_")
#define DWARVEN_RACE_GUILD_BELT_ID (DWARVEN_RACE_GUILD_PREFIX + "belt")

/* Skill decay. */
#define DWARVEN_RACE_GUILD_DECAY   (DWARF_DIR + "train")

#define DWARVEN_RACE_GUILD_BOARD   (BOARD_DIR + "dwarf_guild")

#define DWARVEN_RACE_GUILD_LOG     (LOG_DIR + "dwarf_guild")

#define DWARVEN_RACE_GUILD_SAVE    (DWARF_DIR + "dwarf_save")

/* Shadow definitions for identification and taxation. */
#define DWARVEN_RACE_GUILD_TAX     (2)
#define DWARVEN_RACE_GUILD_NAME    ("Rockfriend guild")
#define DWARVEN_RACE_GUILD_SHORT   ("rockfriend")
#define DWARVEN_RACE_GUILD_STYLE   ("race")
#define DWARVEN_RACE_GUILD_TYPE    ("race")

#define DWARVEN_RACE_GUILD_GOD \
    ((TP->query_race() == "dwarf") ? "Mahal" : "Aule")

#define SILVER_BEARD_AGE           4320000 /* 100 days in heartbeat */

#define IS_MEMBER(p) ((p)->query_guild_name_race() == DWARVEN_RACE_GUILD_NAME)

/* No definitions below this line */
#endif DWARVEN_RACE_GUILD_DEFINITIONS
