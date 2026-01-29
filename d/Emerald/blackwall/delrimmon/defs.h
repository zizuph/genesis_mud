/*
 *  /d/Emerald/blackwall/delrimmon/defs.h
 *
 *  Local defs for the Blackwall Mountains area.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 */

#include "/d/Emerald/sys/paths.h"

#ifndef DEL_RIMMON_DEFS
#define DEL_RIMMON_DEFS

#define MIN_AWARE    15
#define RANDOM_AWARE 10
#define DEL_RIMMON_LOADED    "_del_rimmon_loaded"
#define DR_I_DID_ATTACK      "_dr_i_did_attack"
#define DR_I_ENEMY           "_dr_i_enemy"
#define DR_I_FOUND_CRACK     "_dr_i_found_crack"
#define DR_LAKESHORE         "_lakeshore"
#define MASTER_FILE          (DELRIMMON_DIR + "del_rimmon")

/* from /d/Emerald/ctower/ctower.h */
#define CTOWER_QUEST_NAME "crystal_torque"
#define TORQUE_DIR            ("/d/Emerald/torque/")

#define CTOWER_MANAGER (TORQUE_DIR + "ctower_manager")
#define CTOWER_TORQUE_MANAGER (TORQUE_DIR + "torque_manager")

#define CTOWER_OBJ            TORQUE_DIR + "obj/"
#define CTOWER_TORQUE      (CTOWER_OBJ + "torque")
#define CTOWER_TORQUE_BASE (CTOWER_OBJ + "torque_base")

#define CTOWER_TORQUE_ID   "ctower_torque"

/* vision definitions */
#define VISION_TEST         ("del_test_vision")
#define UNBOUND_VISION      ("del_unbound_vision")
#define BOUND_VISION        ("del_bound_vision")
#define VAMP_VISION         ("del_vamp_vision")

#define LOG_FILE            ("del_rimmon/")
#define DELRIMMON_DIR       (DEL_RIMMON_DIR)
#define MANAGER             (DELRIMMON_DIR + "obj/quest_manager")
#define BEACON              (DELRIMMON_DIR + "obj/beacon")
#define FALLROOM            (DELRIMMON_DIR + "lakeside/caves/fallroom")
#define TORQUE_OBJECT       ("/d/Emerald/ctower/obj/torque")
#define FLUX_PROP           "_del_rimmon_corporeal_flux"
#define TOUCH_PROP          "_del_rimmon_touching_rune"
#define SEEN_PROP           "_del_rimmon_saw_portal"
#define BADNESS             "_akugla_badness_spell_effect"

#define STUMP               ("del_rimmon_quest_stump")
#define CLIFF               ("del_rimmon_quest_cliff")
#define SAND                ("del_rimmon_quest_sand")
#define CLEARING            ("del_rimmon_quest_clearing")
#define BOULDER             ("del_rimmon_quest_boulder")

#define SIGNAL_PATTERN_1    ("signal_pattern_1")
#define SIGNAL_PATTERN_2    ("signal_pattern_2")
#define SIGNAL_PATTERN_3    ("signal_pattern_3")
#define SIGNAL_PATTERN_4    ("signal_pattern_4")
#define SIGNAL_PATTERN_5    ("signal_pattern_5")

/*
 * This prop lets us designate players as enemies of Blackwall.
 */
#define BW_I_ENEMY       "_blackwall_i_enemy"

/*
 * At what alignment do we want our npcs to consider players to be
 * enemies?
 */
#define ENEMY_ALIGNMENT    200

/* logging macros. comment out the first DEBUG_LOG (or TMP_LOG)
 * and uncomment the second to turn off debugging (or tmp logging)
 */
#define DEBUG_LOG(x)    log_file(LOG_FILE + "asks", \
        "DBG "+ctime(time())+" "+file_name(this_object())+"\nDBG\t"+x);


/* Macros included to comply with old Gondor norms */

#define TP               this_player()
#define TI               this_interactive()
#define TO               this_object()
#define TPQN             this_player()->query_name()
#define TPQRN            this_player()->query_real_name()
#define QVB              query_verb()
#define BSN(x)           (x + "\n")
#define NF(x)            notify_fail(x)
#define NF0(x)           { NF(x); return 0; }
#define NFN(x)           NF(BSN(x))
#define NFN0(x)          { NFN(x); return 0; }
#define ENV              environment
#define CAP(x)           capitalize(x)
#define LOW(x)           lower_case(x)
#define WRITE(x)         write(BSN(x))

#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())
#define PRONOUN(x)       ((x)->query_pronoun())
 
#define SET_MAX_HP       set_hp(query_max_hp());
#define SET_MAX_MANA     set_mana(query_max_mana());
#define SET_MAX_FATIGUE  set_fatigue(query_max_fatigue());
#define REFRESH          refresh_mobile();
 
#define QRACE(x)         ((x)->query_race())
#define	QRACENAME(x)	((x)->query_race_name())
 
#define ONE_OF_LIST(array) one_of_list(array)
#define ONE_OF_LIST_WITH_SEED(array, seed) one_of_list((array), (seed))

/* return v if v is an array; otherwise return array containing v.
 * v must be of type mixed.
 */
#define	ARRAY(v)	(pointerp(v) ? (v) : ({ (v) }))

/* this does the same thing as the exclude_array() efun, in 1/3 the time */
#define	EXCLUDE_ARRAY(a, i, j) \
  ((j) ? ((i) ? (a[..((i)-1)]+a[((j)+1)..]) : a[((j)+1)..]) : a[1..])

/* return number within specified range */
#define	CHECK_RANGE(x, min, max) \
    ((x) <= (min) ? (min) : ((x) >= (max) ? (max) : (x)))

/* check if ob can see in specified room */
#define CAN_SEE_IN_OTHER_ROOM(ob, room)	\
    ((room)->query_prop(OBJ_I_LIGHT) > -((ob)->query_prop(LIVE_I_SEE_DARK)))
#define G_TP          (this_player())
#define G_BSN(x)      (break_string((x), 74) + "\n")
#define G_METNAME(x)  ((x)->query_name())
#define G_TNONMET(x)  ("the " + (x)->query_nonmet_name())
#define G_CTNONMET(x) ("The " + (x)->query_nonmet_name())
 

#undef SAY
#define SAY(x)                           \
    say( ({ BSN(G_METNAME(G_TP) + (x)),  \
          BSN(G_CTNONMET(G_TP) + (x)), \
          BSN("Someone" + (x)) }) )

#define FIX_EUID         { setuid(); seteuid(getuid()); }


#endif /* DEL_RIMMON_DEFS */
