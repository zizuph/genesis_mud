/*
 *  /d/Genesis/imbuement/shadows/slow_effect.c
 *
 *  The slowness "poison" caused by slow_shadow
 *
 *  2010/09/13 Lavellan
 */
#pragma strict_types

inherit "/std/object";
#include "../imbuement.h"
#include <macros.h>

/* Definitions */
#define SLOW_AMOUNT         ({-20, -40, -60})
#define EXPIRE_TIME         120.0

/* Global Variables */
public int               Power_Level = 1;
public int               Expire_Alarm;

/* Prototypes */
public void              create_object();
public void              set_level(int level);
public void              start_slow(object attacker);
public void              restart_slow();
public void              stop_slow();

/*
 * Function name:        create_object
 * Description  :        invisible object
 */
public void
create_object()
{
    add_name("_imbue_slow_effect");

    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
} /* create_object */


/*
 * Function name:        set_level
 * Description  :        set the level of the imbuement
 */
public void
set_level(int level)
{
    Power_Level = level;
} /* set_level */


/*
 * Function name:        start_slow
 * Description  :        set the LIVE_I_QUICKNESS
 */
public void
start_slow(object attacker)
{
//    environment()->add_prop(LIVE_I_QUICKNESS, SLOW_AMOUNT[Power_Level-1]);
    environment()->inc_prop(LIVE_I_QUICKNESS, SLOW_AMOUNT[Power_Level-1]);
    environment()->catch_tell("You feel " + POWER_DESC[Power_Level] 
        + "ly lethargic!\n");
    attacker->catch_tell(environment()->query_The_name(attacker)
        + " suddenly stiffens as your weapon strikes, and seems a bit "
        + "lethargic as a result!\n");
    environment()->tell_watcher(QCTNAME(environment()) + " suddenly seems"
        + " a bit lethargic!\n", attacker);
    Expire_Alarm = set_alarm(EXPIRE_TIME, 0.0, stop_slow);
} /* start_slow */


/*
 * Function name:        restart_slow
 * Description  :        restart (extend duration) of effect
 */
public void
restart_slow()
{
    remove_alarm(Expire_Alarm);
    Expire_Alarm = set_alarm(EXPIRE_TIME, 0.0, stop_slow);
} /* restart_slow */


/*
 * Function name:       stop_slow
 * Description  :       remove slowness
 */
void
stop_slow()
{
//    environment()->remove_prop(LIVE_I_QUICKNESS);
    environment()->dec_prop(LIVE_I_QUICKNESS, SLOW_AMOUNT[Power_Level-1]);
    environment()->catch_tell("You are no longer feeling "
        + POWER_DESC[Power_Level] + "ly lethargic.\n");
    environment()->tell_watcher(QCTNAME(environment()) + " shakes "
        + environment()->query_possessive() + " head, seeming to come out of "
        + environment()->query_possessive() + " lethargic state.\n", 0);
    remove_object();
} /* stop_slow */
