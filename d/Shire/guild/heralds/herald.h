/*
 * /d/Shire/herald/herald.h
 *
 * Some definitions for the Heralds of the Valar layman guild
 */

#include "/d/Shire/bits.h"
#ifndef HERALD_DEFINITIONS
#define HERALD_DEFINITIONS

#define HERALD_GUILD_NAME        "Heralds of the Valar"
#define HERALD_GUILD_STYLE       "cleric"
#define HERALD_GUILD_TYPE        "layman"
#define HERALD_GUILD_TAX         15
#define HERALD_GUILD_ALIGN_MIN   -100

#define HERALD_GUILD_MASTER  ({"arman", "finwe" })

#define HERALD_DIRECTORY     "/d/Shire/guild/heralds/"
#define HERALD_SPELLS        (HERALD_DIRECTORY + "spells/")
#define HERALD_SPELLS_OBJ    (HERALD_SPELLS + "obj/")
#define HERALD_DATA          (HERALD_DIRECTORY + "data/")
#define HERALD_BOOKS         (HERALD_DIRECTORY + "books/")
#define HERALD_ROOM          (HERALD_DIRECTORY + "room/")
#define HERALD_LIBS          (HERALD_DIRECTORY + "lib/")
#define HERALD_GUILD_OBJ     (HERALD_DIRECTORY + "obj/")
#define HERALD_LOGS          (HERALD_DIRECTORY + "log/")
#define HERALD_HELP          (HERALD_DIRECTORY + "help/")
#define HERALD_NEWS          (HERALD_HELP + "news")
#define HERALD_GUILD_TRAINER (HERALD_ROOM + "train")
#define HERALD_GUILD_LOG     "/d/Shire/log/herald"

#define HERALD_GUILD_SHADOW  (HERALD_DIRECTORY + "shadow/herald_shadow")
#define HERALD_GUILD_SOUL    (HERALD_DIRECTORY + "soul/herald_soul")
#define HERALD_GUILD_ITEM    (HERALD_DIRECTORY + "obj/robe")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")

// Standard spell stat weighting for cleric guild class
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_WIS, SKILL_WEIGHT, 20, TS_INT, SKILL_WEIGHT, 20, TS_DIS })

// Master Objects
#define HERALD_MANAGER       (HERALD_LIBS + "heralds_manager")

//  Guild member defines
#define IS_MEMBER(p)                ((p)->query_guild_name_lay() == HERALD_GUILD_NAME)
#define HERALD_CORRUPTION(p)        (HERALD_MANAGER->query_herald_corruption(p))
#define ADD_CORRUPTION(p, x)        (HERALD_MANAGER->add_herald_corruption(p, x))
#define REDUCE_CORRUPTION(p, x)     (HERALD_MANAGER->reduce_herald_corruption(p, x))
#define QUERY_HERALD_FOCUS(p)       (HERALD_MANAGER->query_herald_focus(p))
#define SET_HERALD_FOCUS(p, s)      (HERALD_MANAGER->set_herald_focus(p, s))
#define QUERY_HERALD_MAINTAINING(p) (HERALD_MANAGER->query_herald_maintained_spells(p))


#define MEMBER_TRACKER              "/d/Shire/herald/tracker.c"
#define MEMBER_SAVE                 HERALD_DIRECTORY + "members"

#define HERALD_DEBUG(x)	       find_player("arman")->catch_msg("[Herald] " + x + "\n")

/* No definitions below this line */
#endif HERALD_DEFINITIONS
