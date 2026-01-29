/*******************************************************
 *   defs.h
 *
 *   All files in Kalad should include this file.
 *   It contains common definitions for the Kalad domain.
 *   Place path definitions and useful macros here.
 *******************************************************/


/*******************************************************
 *   Standard include files
 *******************************************************/
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <const.h> 
#include <money.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>
#include "/d/Kalad/sys/time.h"
/* No longer included: <std.h>*/


/*******************************************************
 *   Common useful macros
 *******************************************************/
#define BS(msg)          break_string(msg,70)
#define TP               this_player()
#define TP_N             TP->query_name()
#define TO               this_object()
#define PO               previous_object()
#define AA(xx,yy)        add_action("xx","yy")
#define E(obj)           environment(obj)
#define P(str,ob)        present(str,ob)
#define NF(xxx)          notify_fail(xxx)
#define C(xxx)           capitalize(xxx)
#define L(str)           lower_case(str)
#define HE(who)          who->query_pronoun()
#define HIS(who)         who->query_possessive()
#define HIM(who)         who->query_objective()
#define AINV(ob)         all_inventory(ob)
#define DINV(ob)         deep_inventory(ob)
#define FN(ob)           file_name(ob)
#define ALARM(time,fun)  set_alarm(time,0.0,"fun") /* an easy alarm     */

#define RTILDE(str)      "/sys/global/filepath"->reduce_to_tilde_path(str)
/* given a string such as "/d/Kalad/ashbless/obj", this macro will
   return the tilde path for the string such as "~ashbless/obj"         */
   
#define KLOG(file,str)   log_file(file,"\n"+GTIME+"\n"+str)
/* log an entry (including current time and date) in the appropriate
   file in the Kalad log directory (or the one in your home directory)  */
   
   
#define MTAIL(file,func) STD(more)->mtail(file,func)
/* Tail a file in "more" format so the viewer can go back if necessary  */


/************************************************************************
 *   The following swiped from Napture:
 *
 *   Example: If this_player() was "ashbless",
 *    SAYNAME("A big mallet hits "," on the head and everyone laughs.");
 *    would produce one of these messages (dependent on the met/visibility
 *    situation of the onlooker):
 *
 *    "A big mallet hits Ashbless on the head and everyone laughs.",
 *    "A big mallet hits the nondescript unknown male human wizard on the
 *     head and everyone laughs.",
 *    "A big mallet hits someone on the head and everyone laughs.".
 ************************************************************************/
#define SAYNAME(x1,x2)     say( ({ C(x1 + TP_N + x2),  \
       C(x1 + "the " + TP->query_nonmet_name() + x2),  \
       C(x1 + "someone" + x2) }), TP)


/*******************************************************
 *   Kalad domain specific skill(s)
 *******************************************************/
#define SS_POISON        135000     /* Duiss Aszbhar guild skill          */
#define SS_WOLF_RIDING   135001     /* Red Fang guild wolf-riding skill   */
#define SS_PREF_WEP      135002     /* Shadow Walkers                     */
#define SS_BOOMERANG     135003     /* Olden Elves                        */
#define SS_WHIRLWIND     135004     /* Death Knights of the Khiraa        */
#define SS_BASHSTUN      135005     /* Death Knights of the Khiraa        */
#define SS_GOUGE         135006     /* Lich Priesthood of the Khiraa      */
#define SS_WOLF_HANDLING 135007     /* Red Fang Riders                    */

#define TDESC   TO->query_time_desc()             
/* returns the time-based description for this room                       */

#define GTIME   ctime(time())                      
/* return current Genesis time in a nice string format. Useful for logs.  */


/*******************************************************
 *   For rooms only
 *******************************************************/
#define IN_CITY             query_in_kabal()
/* returns 1 if this room is in the city of kabal                         */

#define INSIDE              add_prop(ROOM_I_INSIDE,1)
/* makes this room an inside room                                         */

#define SEWER_I_NO_STENCH   "_sewer_i_no_stench"
#define ROOM_I_DIRTY         "_room_i_dirty"
/* this prop holds the dirtiness level of a room                          */
           
#define DIRTY(value)        add_prop(ROOM_I_DIRTY, value)
/* use this macro to set the dirtiness level in a room                    */

#define SHOP                "@@shop@@"
/* Use this as your exit function in rooms leading to a shop              */

#define ROOM_NO_TIME_DESC   "_room_i_no_time_desc"
/* don't show a time description in this room                             */


/*******************************************************
 *   Macros for room events (local events)
 *******************************************************/
#define EVENTS_ON          set_allow_events(1)
/* turn local events on for this room.                                    */        

#define EVENTS_OFF         set_allow_events(0)
/* turn local events off for this room.                                   */        

#define QEON               query_allow_events()
/* are events turned on for this room? returns: 1=yes, 0=no               */

#define SET_ETIME(i)       set_event_interval(i)
/* set time between events for this room. i can be an int or float.       */

#define QETIME             query_event_interval()
/* returns time between events (float)                                    */

#define EVENT(msg)         new_event(msg)
/* add a new event message to this room. msg should be a string.          */

#define RMEVENT(msg)       remove_event(msg)
/* remove a specific event message from this room. msg should be a string.*/

/*******************************************************
 *   For npcs
 *******************************************************/


/*******************************************************
 *   Guild macros
 *******************************************************/

/*   Membership checks: retruns true if ob is member of that guild */
#define IS_SHADOW(ob)   ob->test_bit("Kalad",4,0)
#define IS_ZINTRA(ob)   ob->test_bit("Kalad",4,2)
#define IS_THANAR(ob)   ob->test_bit("Kalad",4,4)
#define IS_DROW(ob)     ob->test_bit("Kalad",4,5)
#define IS_FANG(ob)     ob->test_bit("Kalad",4,8)
#define IS_OLDANI(ob)   ob->test_bit("Kalad",4,9)


/*******************************************************
 *   For weapons
 *******************************************************/
 
/*   Weapon drawbacks for Kalad weapons - more realistic
 *                         dull  corr  break          
 */


/*******************************************************
 *   Misc properties
 *******************************************************/
#define LIVE_I_DIRTY   "_live_i_dirty"   /* how dirty is the player? */
#define IN_WATER       "in_water"        /* living is in water       */
#define UNDEAD_I_NO_AUTO "_undead_i_no_auto" /* undead_std monster no 
                                                auto attacks */

/*******************************************************
 *   Raumdor guards
 *******************************************************/
#define IS_ENEMY_OF_DRAKMERE   "_is_enemy_of_drakmere"
#define IS_ENEMY_OF_TORBODON   "_is_enemy_of_torbodon"

/****************************************************************************
 *   Path macros
 ****************************************************************************/
#define KALAD(obj)   "/d/Kalad/obj"            /* Kalad General Directory   */
#define COMMON(obj)  "/d/Kalad/common/obj"     /* Common directory          */
#define OPEN(obj)    "/d/Kalad/open/obj"       /* Open directory            */
#define CLONE(obj)   "/d/Kalad/clone/obj"      /* standard clones directory */
#define STD(obj)     "/d/Kalad/std/obj"        /* standard inherits dir     */
#define LOGS(obj)     KALAD(log/obj)           /* Kalad logs directory      */

#define MARKET(obj)  "/d/Kalad/common/market/obj"     /* Market District    */
#define PORT(obj)    "/d/Kalad/common/port/obj"       /* Port District      */
#define SEWERS(obj)  "/d/Kalad/common/sewers/obj"     /* Sewers under city  */
#define CENTRAL(obj) "/d/Kalad/common/central/obj"    /* Central district   */
#define TRADE(obj)   "/d/Kalad/common/trade/obj"      /* Tradesmen's Dist   */
#define NOBLE(obj)   "/d/Kalad/common/noble/obj"      /* Upper Class Dist   */
#define CVAN(obj)    "/d/Kalad/common/caravan/obj"    /* Caravan District   */

#define CPASS(obj)   "/d/Kalad/common/wild/pass/obj" /* pass Ne of city     */
#define WILD(obj)    "/d/Kalad/common/wild/obj"      /* Outside the city    */
#define FARM(obj)    "/d/Kalad/common/wild/farm/obj"
#define CANTHYR(obj) "/d/Kalad/common/canthyr/obj"   /* Empire of Canthyr   */
#define RAUM(obj)    "/d/Kalad/common/raum/obj"      /* Land of Raumdor     */
#define KALDORO(obj) "/d/Kalad/common/wild/pass/kaldoro/obj"
                                             /* farmlands area west of city */

#define GUILDS(obj)  "/d/Kalad/common/guilds/obj"        /* Guilds dir      */
#define ZINTRA(obj)  "/d/Kalad/common/sewers/zintra/obj" /* Zintra Guild    */

#define ASH(obj)     "/d/Kalad/ashbless/obj"        /* Ashbless's Directory */
#define SANDY(obj)   "/d/Kalad/sandalphon/obj"      /* Sandy's Directory    */

/*******************************************************
 *   Obsolete (only here for back compatability)
 *******************************************************/
#define MRKT_PATH(obj)    "/d/Kalad/common/market/obj"
#define MRKT_IN_NO_HEAR   "_mrkt_in_no_hear"
/*   set this prop in: indoor rooms in market that can't hear outside events*/
#define GUILD(obj)   "/d/Kalad/common/guild/obj"


/***************************************************
 *    Props for equipment.
 ***************************************************/
#define KVWEP(xxx)  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_pen(), \
                    query_hit()) + (random(xxx) - (xxx / 2)))
#define KWWEP(xxx)  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON( \
                    query_pen(), query_wt()) + (random(xxx) - (xxx / 2)))
#define KVARM(xxx)  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) \
                    + (random(xxx) - (xxx / 2)))
#define KWARM(xxx)  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( \
                    query_ac(), query_at()) + (random(xxx) - (xxx / 2)))

#define KVOLUME     add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5)
/* or.. */
#define KVOL(xxx)   add_prop(OBJ_I_VOLUME, ftoi(kalc_vol("xxx", \
                    query_prop(OBJ_I_WEIGHT))))


