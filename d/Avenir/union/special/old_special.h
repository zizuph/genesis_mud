#ifndef __UNION_SPECIAL_ATTACKS__
#define __UNION_SPECIAL_ATTACKS__

#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

#include "../defs.h"
#include "../lib/filters.h"
/*
 * UNDEF   to disable debugging output.
 * DEFINE  to enable  debugging output.
 */
#undef COMBAT_DEBUG

/* combat aid % */
#define FLING_CAID	81
#define SLASH_CAID	65

/* cb_tohit value */
// 66% chance
//#define FLING_TOHIT	90

// Increased due to negative feedback - Arman, June 2020
// Reduced due to changes in fling/slash - Carnak, April 2021
#define FLING_TOHIT	80
#define SLASH_TOHIT	80

// sway unerring boosts hit chance for slash and fling
#define UNERRING_HIT_BONUS    25
// sway aggressively decreases hit chance for fling and slash
// hit chance being 82% and 75%
#define AGG_HIT_PENALTY       20

#define DRUNK_LIMIT	25
#define ENCUMB_FLING	60
#define ENCUMB_SLASH	75

/* Formula to reduce effectiveness */
#define EFF_REDUCE(x, y)	(x + ((y / 2) - random(y)))

/* Fatigue cost per special */
//#define SPECIAL_FATIGUE		(2 + random(2))
// Temporarily lowered to 1 until I have had a chance to review it.
#define SPECIAL_FATIGUE     1

/* Special skills and stats */
#define FLING_SKILLS	({ SKILL_WEIGHT, 50, SS_FLING, SKILL_WEIGHT, 50, SS_WEP_KNIFE })
#define FLING_STATS	({ SKILL_WEIGHT, 50, TS_DEX, SKILL_WEIGHT, 50, SKILL_AVG, TS_STR, TS_DIS, SKILL_END })
#define SLASH_SKILLS	({ SKILL_WEIGHT, 50, SS_SLASH, SKILL_WEIGHT, 50, \
	SKILL_AVG, SS_WEP_SWORD, SS_WEP_KNIFE, SKILL_END })
#define SLASH_STATS	({ SKILL_WEIGHT, 50, TS_STR, SKILL_WEIGHT, 50, SKILL_AVG, TS_DEX, TS_DIS, SKILL_END })

/* Special Prep Time */
#define MIN_FLING_PREP		3
#define MAX_FLING_PREP		10
#define MIN_SLASH_PREP		1
#define MAX_SLASH_PREP		4

/* Special Recover Time */
#define MIN_FLING_RECOVER	6
#define MAX_FLING_RECOVER	10
#define MIN_SLASH_RECOVER	9
#define MAX_SLASH_RECOVER	16
/*
 * FLING: Min  3 +  3 = 6
 * 	  Max 10 + 10 = 20
 *
 * SLASH: Min  1 +  9 = 10
 *        Max  4 + 16 = 20
 */
#define ME(x)	TP->catch_msg(x + "\n")
#define YOU(x)	target->catch_msg(x + "\n");
#define TW(x)	TP->tell_watcher(x + "\n", target);
#define TWM(x)	TP->tell_watcher_miss(x + "\n", target);
/*
 * Definitions for the Sway
 */
#define SWAY_OBJ         (SPECIAL + "sway_obj")
#define SWAY_OBJ_INERR   (SPECIAL + "sway_obj_unerringly")
#define SWAY_OBJ_AGG     (SPECIAL + "sway_obj_aggressively")

#define SWAY_PHASE_PROP  "_shadow_union_sway_phase"

#define SWAY_MANA	20
#define SWAY_FATIGUE	10
/* .001% of the MAX Flame state */
#define SWAY_FLAME_COST	10

/*
 * Standard wound object
 */
#define WOUND_OBJ	"/d/Genesis/specials/std/wounding_obj_base"

#endif /* __UNION_SPECIAL_ATTACKS__ */
