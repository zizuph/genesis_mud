#include <alignment.h>
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/guild/pot/admin/admin.h"
#include "/d/Genesis/login/login.h"


#define GUILD_NAME            "Priests of Takhisis"
#define GUILD_SHORT_NAME      "pots"
#define GUILD_TYPE            "occupational"
#define GUILD_STYLE           "cleric"
#define GUILD_TAX             35


// TODO: Move to the pot directory
#define POT_DIR         "/d/Ansalon/guild/pot/" 
#define GUILD_ADMIN     (POT_DIR + "admin/admin")

//#define POT_DATA            POT_DIR + "data/"
//#define POT_HELP            POT_DIR + "help/"
//#define POT_OBJS            POT_DIR + "objs/"
//#define POT_NPCS            POT_DIR + "npcs/"
//#define POT_LOGS            POT_DIR + "logs/"
//#define POT_LIBS            POT_DIR + "lib/"
#define POT_SHADOWS         "/d/Ansalon/guild/new_pot/shadows/"
//#define POT_SPECIALS        POT_DIR + "specials/"
#define POT_SPELLS          "/d/Ansalon/guild/new_pot/spells/"
#define POT_SPELL_OBJS      "/d/Ansalon/guild/new_pot/spells/objs/"
#define POT_SOULS           "/d/Ansalon/guild/new_pot/souls/"
//#define POT_BOARD_NOTES     POT_DIR + "board_notes/"
#define POT_STD             "/d/Ansalon/guild/new_pot/std/"

// Guild Locations
//#define POT_TEMPLE          POT_DIR + "temple/"
#define RACES_BLOCK     ({ "kender", "hobbit", "dwarf" })

// Shadows and Souls
#define POT_SOUL                  (POT_SOULS + "pot_soul")
#define POT_SHADOW                (POT_SHADOWS + "pot_shadow")
#define SPELL_MANAGER_SOUL       ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define MANA_SHADOW              ("/d/Genesis/specials/guilds/shadows/mana_shadow")
#define GUILD_CMDSOUL POT_SOUL
#define GUILD_START     NTEMPLE + "lvl2/dorm"
#define GUILD_PO        NTEMPLE + "lvl2/post"
#define GUILD_LIB       NTEMPLE + "lvl2/library"

#define PS_GUILD_LEVEL     (143004)
#define PS_SPELLS          (143005)
#define PS_SKILL_POINTS    (143008)
#define PS_STANDING        (143007)
#define PS_NUM  ({ PS_GUILD_LEVEL, PS_SPELLS, PS_SKILL_POINTS, })
#define PS_DESC ({ "", "", "", })
#define PS_STANDING_MIN     -1200
#define PS_STANDING_MAX     1200

#define GUILDHELP       POT_DIR + "help/"

// Master Objects
//#define GUILD_MANAGER            (POT_LIBS + "guild_manager")

// Guild NPCS
//#define POT_GUILDMASTER (POT_NPCS + "guildmaster")

// Useful Macros
//#define IS_GUILDMASTER(x)    IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_POT(x)            (x)->is_priest()
#define RND_RANGE(base, range) \
    (random(2) ? base + random(max(range / 2, 1)) : \
    base - random(max(range / 2, 1)))

#define ADJUST_STANDING(current, how_much) \
    ((current <= 0 || how_much <= 0 ) ? current + how_much : \
    current + max(how_much / max((current / 100), 1), 1))
    
    
#define ATAX            13
#define MTAX            20
#define HTAX            22

#define TAX_ARRAY       ({ ATAX, MTAX, HTAX, })


#define GUILD_LEVEL_INITIATE    0
#define GUILD_LEVEL_PRIEST      1
#define GUILD_LEVEL_HIGH_PRIEST 2


#define MEDALLION_ID    "_pot_takhisis_medallion"
#define MEDALLION_OBJ   POT_DIR + "obj/medallion"

#define MEMBER(pl)      (pl->query_guild_member(GUILD_NAME))


/* Male (and neuter) titles     Female titles */
#define GUILD_TITLES    ({                              \
({                                                      \
        "Initiate",             "Initiate",             \
        "Acolyte",              "Acolyte",              \
        "Deacon",               "Deacon",               \
        "Adept",                "Adept",                \
        "Dragon Cleric",        "Dragon Cleric",        \
}), ({                                                  \
        "Priest",               "Priestess",            \
        "Canon",                "Canon",                \
        "Demon Priest",         "Demon Priestess",      \
        "Spiritor",             "Spiritor",             \
        "Nightreaver",          "Nightreaver",          \
}), ({                                                  \
        "High Priest",          "High Priestess",       \
        "Dark Bishop",          "Dark Bishop",          \
        "Dragonlord",           "Dragonlady",           \
        "Nightmaster",          "Nightmistress",        \
        "Nightlord",            "Nightlady",            \
}) })

/*
 * Note that both sets are used - the second set when the 
 * council members focus on a task... aka.. they decide
 * to show it.
 */
#ifndef ORG_COUNCIL_TITLES
#define COUNCIL_TITLES ({ \
        "leader", \
        "herbmanager", \
        "inquisitor", \
        "librarian", \
        "mentor" })
#else
#define COUNCIL_TITLES  ({                              \
        "High Inquisitor",                              \
        "Grand Dragon",                                 \
        "Master Chronicler",                            \
        "Dark Sage",                                    \
        "Lord Preacher",                                \
        })
#endif

#define TITLES_COUNCIL ([ \
    "leader"   : ({ ({ "Nightlord of Takhisis" }), \
                    ({ "Nightlady of Takhisis" }), \
                    ({ }) }), \
    "inquisitor"  : ({ "High Inquisitor of Takhisis", \
                       "Wrath of Takhisis" }), \
    "herbmanager" : ({ "Chief Herbalist of Takhisis" }), \
    "librarian"   : ({ "Diplomatic Envoy of Takhisis", \
                       "Dark Sage of Takhisis", \
                       "Master Chronicler of Takhisis" }), \
    "mentor"      : ({ "Head Mentor of Takhisis", \
                       "Lord Preacher of Takhisis", \
                  "Lady Preacher of Takhisis", \
                       "Dark Tutor of Takhisis" }) \
    ])

#define POT_SPECIAL_TITLE       "_pot_special_title"

/* Alignment max for      cleric      priest        high priest */
#define ALIGN_LIMIT     ({ -200,         -50,            100 })
