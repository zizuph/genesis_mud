/*******************************************************
 *   defs.h
 *
 *   All files in the domain should include this file.
 *******************************************************/

/*******************************************************
 * Standard include files
 *******************************************************/
#include <cmdparse.h>
#include <composite.h>
#include <const.h> 
#include <exec.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

/*******************************************************
 *   Common useful macros
 *******************************************************/
#define AINV(ob)    all_inventory(ob)
#define E(obj)      environment(obj)
#define HE(who)     who->query_pronoun()
#define HIS(who)    who->query_possessive()
#define HIM(who)    who->query_objective()
#define NF(xxx)     notify_fail(xxx)

#define KLOG(file,str)   log_file(file,"\n"+GTIME+"\n"+str)

#define OBJ_IN_ARRAY(f,a) filter(a, \
  &operator(==)(f) @ &operator([])(,0) @ &explode(, "#") @ file_name)

#define OBJ_IN_INV(f,p) sizeof(OBJ_IN_ARRAY(f,INV(p)))

/*******************************************************
 *   Domain specific skill(s)
 *******************************************************/
#define SS_WHIRLWIND     135004     /* Death Knights of the Khiraa        */
#define SS_BASHSTUN      135005     /* Death Knights of the Khiraa        */
#define SS_GOUGE         135006     /* Lich Priesthood of the Khiraa      */

/*******************************************************
 * For NPCs
 *******************************************************/
#define STAT_ARRAY(num) ({num, num, num, num, num, num})

/*******************************************************
 * Misc. properties
 *******************************************************/
#define UNDEAD_I_NO_AUTO        "_undead_i_no_auto"
#define IS_ENEMY_OF_DRAKMERE    "_is_enemy_of_drakmere"
#define LIVE_AO_KNOWN_ENEMY     "_live_ao_known_enemy"
#define OBJ_I_CAN_BE_PULLED     "_obj_i_can_be_pulled"
#define ROOM_I_HELP_CALLED      "_room_i_helped_called"

/*******************************************************
 * Path macros
 ******************************************************/
#define DOMAIN          "Raumdor"
#define DOMAIN_DIR      "/d/" + DOMAIN + "/"

#define COMMON_DIR      DOMAIN_DIR + "common/"
#define DOC_DIR         DOMAIN_DIR + "doc/"
#define LIB_DIR         DOMAIN_DIR + "lib/"
#define OBJ_DIR         DOMAIN_DIR + "obj/"
#define SOULS_DIR       DOMAIN_DIR + "souls/"
#define SPECIALS_DIR    DOMAIN_DIR + "specials/"
#define STD_DIR         DOMAIN_DIR + "std/"
#define STEEDS_DIR      DOMAIN_DIR + "steeds/"

#define STD_ROOM        STD_DIR + "room"
#define STD_MONSTER     STD_DIR + "monster"
#define STD_UNDEAD      STD_DIR + "undead"

/*******************************************************
 *  Time
 *******************************************************/
#define CLOCK	    (LIB_DIR + "clock")
#define DAY         CLOCK->query_day()
#define DAYBREAK    6
#define NIGHTFALL   20

#define ROOM_M_CANNOT_TELL_TIME "_raumdor_room_m_cannot_tell_time"
#define ROOM_NO_TIME_DESC   "_room_i_no_time_desc"

#define GTIME   ctime(time())                      

/*******************************************************
 * Money
 *******************************************************/
#define COPPER_VALUE    MONEY_VALUES[MONEY_CC_INDEX]
#define SILVER_VALUE    MONEY_VALUES[MONEY_SC_INDEX]
#define GOLD_VALUE      MONEY_VALUES[MONEY_GC_INDEX]
#define PLATINUM_VALUE  MONEY_VALUES[MONEY_PC_INDEX]


/*******************************************************
 * Definitions from other domains
 *******************************************************/
// Prevent Monk's plexus with M_PROP_LIVE_NO_SPECIAL + "plexus"
#define M_PROP_LIVE_NO_SPECIAL  "_live_m_no_"

// Prevent ranger specials
#define RANGER_M_NOT_BRAWL      "_ranger_m_not_brawl"
#define RANGER_I_NOT_BRAWL      "_ranger_i_not_brawl"
#define RANGER_M_NOT_BLIND      "_ranger_m_not_blind"
#define RANGER_I_NOT_BLIND      "_ranger_i_not_blind"
#define RANGER_M_NOT_DISARM     "_ranger_m_not_disarm"
#define RANGER_I_NOT_DISARM     "_ranger_i_not_disarm"
#define RANGER_M_NOT_TRIP       "_ranger_m_not_trip"
#define RANGER_I_NOT_TRIP       "_ranger_i_not_trip"


/***************************************************
 * Darkness & Messaging
 ***************************************************/
#define FILTER_NOT_SEE(x,o) filter(x, &not() @ &->check_seen(o))

#define SEEN(t,o)           (CAN_SEE(o, t) && CAN_SEE_IN_ROOM(o))
#define LIVE(l)             FILTER_LIVE(AINV(l))
#define LIVE_OTHER(l,o)     FILTER_LIVE(AINV(l) - ({o}))
#define LIVE_CAN_SEE(l)     FILTER_CAN_SEE_IN_ROOM(LIVE(l))
#define LIVE_CANNOT_SEE(l)  filter(LIVE(l), &not() @ &->can_see_in_room())
#define LIVE_SEEN(o)        FILTER_IS_SEEN(o, \
                                FILTER_CAN_SEE_IN_ROOM(LIVE_OTHER(E(o),o)))
#define LIVE_NOT_SEEN(o)    (LIVE_OTHER(E(o),o) - LIVE_SEEN(o))
#define LIVE_BLIND(l)       filter(LIVE(l), &->query_prop(LIVE_I_BLIND))
#define LIVE_NOT_BLIND(l)   filter(LIVE(l), \
                                &not() @ &->query_prop(LIVE_I_BLIND))

#define TELL(o,x)               o->catch_msg(x)
#define TELL_LIVE(l,x)          TELL(LIVE(l),x)
#define TELL_CAN_SEE(l,x)       TELL(LIVE_CAN_SEE(l),x)
#define TELL_CANNOT_SEE(l,x)    TELL(LIVE_CANNOT_SEE(l),x)
#define TELL_SEEN(o,x)          TELL(LIVE_SEEN(o),x)
#define TELL_NOT_SEEN(o,x)      TELL(LIVE_NOT_SEEN(o),x)
#define TELL_BLIND(l,x)         TELL(LIVE_BLIND(l), x)
#define TELL_NOT_BLIND(l,x)     TELL(LIVE_NOT_BLIND(l), x)

#define TELL_LIVE_OTHER(l,x,o)          TELL(LIVE_OTHER(l,o), x)
#define TELL_CAN_SEE_OTHER(l,x,o)       TELL((LIVE_CAN_SEE(l) - ({o})),x)
#define TELL_CANNOT_SEE_OTHER(l,x,o)    TELL((LIVE_CANNOT_SEE(l) - ({o})),x)


/***************************************************
 * Standards, bug avoidance 
 ***************************************************/
#define CHECK_DEAD(victim,killer) \
    if (victim->query_hp() <= 0) \
        victim->do_die(killer)

#define DEFAULT_NOTIFY notify_fail(CAP(query_verb()) + " what?\n", 0)


#define FILTER_NOT_UNDEAD(o)    filter(FILTER_LIVE(o), \
                                    &not() @ &->query_prop(LIVE_I_UNDEAD))

#define FILTER_UNDEAD_ENEMIES(o)    filter(FILTER_NOT_UNDEAD(o), \
                                        &not() @ &->query_prop(UNDEAD_I_NO_AUTO))

#define UNDEAD_ENEMY(o) (!(o->query_prop(LIVE_I_UNDEAD) || \
                            o->query_prop(UNDEAD_I_NO_AUTO)))


/***************************************************
 * Debugging
 ***************************************************/
#define DEBUG_FILE (LIB_DIR + "debug")
#define DEBUG_LIST ({"malus","shanoga"})
#define DUMP(v) DEBUG_FILE->dump(DEBUG_LIST,v)
#define STACK DEBUG_FILE->stack()
#define FIX_TP(x) DEBUG_FILE->fix_this_player(x)
