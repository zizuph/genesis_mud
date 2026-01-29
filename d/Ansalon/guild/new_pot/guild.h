/* The definitions for the guild */
/*
 * Revisions:
 *   Lucius, Sep 2016: Change "herbmanager" to "chancellor".
 *                     Also, removed ORG_COUNCIL_TITLES as there
 *                     is no fallback code to revert to these titles.
 *
 */
#ifndef _POT_DEFS_
#define _POT_DEFS_

/* Include the list of spells */
#include <ss_types.h>
#include "spells.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

#define GUILD_NAME	"Priests of Takhisis"
#define GUILD_STYLE	"cleric"
#define ATAX		17
#define MTAX		33
#define HTAX		36
#define TAX_ARRAY	({ ATAX, MTAX, HTAX, })

#define RACES_BLOCK	({ "kender", "hobbit", "dwarf" })

#define TMP_POT_DEDICATION_SCROLL	"_tmp_pot_dedication_scroll"

#define GUILD_LEVEL_INITIATE	0
#define GUILD_LEVEL_PRIEST	1
#define GUILD_LEVEL_HIGH_PRIEST	2

#define DARK_WARRIOR_ASPECT         "_pot_dark_warrior_aspect"
#define DARK_LADY_ASPECT            "_pot_dark_lady_aspect"

#define ACTIVE_ENCHANTMENT "_pot_enchant_weapon_active"

      /* Male / Neuter titles     Female titles */
#define GUILD_TITLES	({ \
({                                                      \
	"Initiate",		"Initiate",		\
	"Acolyte",		"Acolyte",		\
	"Deacon",		"Deacon",		\
	"Adept",		"Adept",		\
	"Dragon Cleric",	"Dragon Cleric",	\
}), ({ \
	"Priest",		"Priestess",		\
	"Canon",		"Canon",		\
	"Demon Priest",		"Demon Priestess",	\
	"Spiritor",		"Spiritor",		\
	"Nightreaver",		"Nightreaver",		\
}), ({ \
	"High Priest",		"High Priestess",	\
	"Dark Bishop",		"Dark Bishop",		\
	"Dragonlord",		"Dragonlady",		\
	"Nightmaster",		"Nightmistress",	\
	"Nightlord",		"Nightlady",		\
}) })

#define COUNCIL_TITLES ({ \
	"leader",	\
	"chancellor",	\
	"inquisitor",	\
	"librarian",	\
	"mentor"	})

#define TITLES_COUNCIL ([ \
    "leader"      : ({ ({ "Nightlord of Takhisis" }),   \
                       ({ "Nightlady of Takhisis" }),   \
                       ({                         })    \
                    }), \
    "inquisitor"  : ({  "High Inquisitor of Takhisis",  \
                        "Wrath of Takhisis"             \
                    }), \
    "chancellor"  : ({  "Lord Chancellor of Takhisis",  \
                        "Lady Chancellor of Takhisis",  \
                        "Dark Seneschal of Takhisis"    \
                    }), \
    "librarian"   : ({  "Diplomatic Envoy of Takhisis", \
                        "Dark Sage of Takhisis",        \
                        "Master Chronicler of Takhisis" \
                    }), \
    "mentor"      : ({  "Head Mentor of Takhisis",      \
                        "Lord Preacher of Takhisis",    \
		        "Lady Preacher of Takhisis",    \
                        "Dark Tutor of Takhisis"        \
                    }), \
])

/* This is the switch to close the guild for new members
 */
#ifdef 0
#define CLOSED_FOR_NEW_MEMBERS  1
#endif

#define MEMBER(pl)	 (pl->query_guild_member(GUILD_NAME))
#define GUILD_LEADER(pl) (GUILD_ADMIN->query_guild_leader() == pl->query_real_name())

#define GUILDDIR	"/d/Ansalon/guild/new_pot/"
#define GUILD_ADMIN	(GUILDDIR + "admin/admin")
#define GUILDDIRSPELL	(GUILDDIR + "spells/")
#define GUILDDIROBJ	(GUILDDIR + "obj/")
#define GUILDDIRSTD	(GUILDDIR + "std/")
#define GUILDNPC	(GUILDDIR + "obj/living/")

#define GUILDHELP	(GUILDDIR + "help/")

#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_WIS, SKILL_WEIGHT, 20, TS_INT, SKILL_WEIGHT, 20, TS_DIS })

#define GUILD_START	(NTEMPLE + "lvl2/dorm")
#define GUILD_PO	(NTEMPLE + "lvl2/post")
#define GUILD_LIB	(NTEMPLE + "lvl2/library")

#define GUILD_CMDSOUL	(GUILDDIR + "soul/cmdsoul")
#define POTSHADOW	(GUILDDIR + "shadow/occ_shadow")

#define SPELL_MANAGER_SOUL       ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define MANA_SHADOW              ("/d/Genesis/specials/guilds/shadows/mana_shadow")

#define SPELLS		(GUILDDIR + "spells/spells")

#define MEDALLION_ID	    "_pot_takhisis_medallion"
#define MEDALLION_ID_NEW    "takhisis_medallion"
#define MEDALLION_OBJ	(GUILDDIR + "obj/medallion")

#define SOULGEM_OBJ	(GUILDDIR + "obj/soul_gem")

#define GUILDMASTERS	({ "arman" })

// 10 per cent combat aid reduction modifier for open beta, 1 meaning applied
// Opening penalty removed.
// #define BETA_CAID_MOD   1    
#define BETA_CAID_MOD   0 

#define DEBUG(x)	find_player("arman")->catch_msg("[PoT] " + x + "\n")

#define PS_GUILD_LEVEL	(143004)
#define PS_SPELLS	(143005)
#define PS_SKILL_POINTS	(143008)
#define PS_STANDING	(143007)

#define PS_NUM  ({ PS_GUILD_LEVEL, PS_SPELLS, PS_SKILL_POINTS, })
#define PS_DESC ({ "", "", "", })

#define Q_VERMINAARD	(1)
#define Q_KALAMAN	(1 << 1)
#define Q_ANTECHAMBERS	(1 << 2)

#define PS_STANDING_MIN	-1200
#define PS_STANDING_MAX	1200

#define ADJUST_STANDING(current, how_much) \
    ((current <= 0 || how_much <= 0 ) ? current + how_much : \
    current + max(how_much / max((current / 100), 1), 1))

#define RND_RANGE(base, range) \
    (random(2) ? base + random(max(range / 2, 1)) : \
    base - random(max(range / 2, 1)))
             
/* Alignment max for      cleric      priest        high priest */
#define ALIGN_LIMIT	({ -200,         -50,            100 })

#define POT_GOT_NEW_SPELL	"_pot_got_new_spell"
#define POT_SPECIAL_TITLE	"_pot_special_title"

/* The guild has fifteen levels. Skills are maxed out at their twelfth.
 * For a more human readable chart, refer to info/skills_spells
 */

//                          1   2   3   4   5   6   7   8   9  10  11
 
#define SKILL_LEVELS ([ \
 SS_SPELLCRAFT :        ({ 50, 50, 50, 50, 50, 75, 88, 90, 93, 94, 100 }),\
 SS_ELEMENT_LIFE :      ({ 50, 50, 50, 50, 50, 75, 88, 90, 93, 94, 100 }),\
 SS_ELEMENT_AIR :       ({ 15, 30, 35, 40, 45, 65, 66, 67, 68, 69, 70 }),\
 SS_ELEMENT_WATER :     ({ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }),\
 SS_ELEMENT_EARTH :     ({ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 }),\
 SS_FORM_TRANSMUTATION: ({  0,  0,  0, 25, 25, 65, 80, 81, 82, 83, 84 }),\
 SS_FORM_ENCHANTMENT :  ({ 15, 30, 35, 40, 45, 65, 66, 67, 68, 69, 70 }),\
 SS_FORM_DIVINATION :   ({ 25, 26, 27, 28, 29, 34, 34, 34, 34, 34, 34 }),\
 SS_FORM_CONJURATION :  ({  0,  0, 20, 30, 50, 75, 78, 80, 83, 84, 90 }),\
 SS_WEP_CLUB :          ({ 30, 40, 50, 60, 64, 64, 64, 64, 64, 64, 64 }),\
 SS_DEFENCE :           ({ 40, 45, 50, 55, 60, 60, 60, 60, 60, 60, 60 }),\
 SS_ALCHEMY :           ({ 30, 30, 30, 34, 34, 34, 45, 45, 45, 45, 60 }),\
 SS_LANGUAGE :          ({ 30, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50 }),\
 SS_HERBALISM :         ({ 40, 50, 50, 50, 60, 60, 60, 60, 60, 60, 60 }),\
 SS_AWARENESS :         ({ 40, 40, 40, 40, 40, 40, 40, 50, 50, 50, 60 }),\
 SS_APPR_MON :          ({ 30, 30, 30, 30, 34, 34, 34, 40, 40, 40, 40 }),\
 SS_APPR_OBJ :          ({ 30, 34, 34, 34, 34, 34, 40, 45, 45, 45, 50 }),\
 SS_APPR_VAL :          ({ 30, 34, 34, 34, 34, 34, 40, 45, 45, 45, 50 }),\
 SS_LOC_SENSE :         ({ 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 60 }),\
 SS_ANI_HANDL :         ({ 30, 30, 40, 40, 40, 40, 50, 50, 50, 50, 60 }),\
 SS_PARRY :             ({ 10, 20, 30, 34, 34, 34, 34, 34, 34, 34, 34 }),\
 SS_WEP_KNIFE :         ({ 30, 30, 30, 40, 40, 50, 50, 50, 50, 50, 50 }),\
])
 
#endif /* _POT_DEFS_ */
