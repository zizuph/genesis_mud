/*
 *  /d/Emerald/herbs/rotbloom_shadow.c
 * 
 *  This object is transfered to players who have come in contact with
 *  a rotbloom cloud. It prevents players from eating for a period of
 *  time.
 * 
 *  Copyright (c) August 2004, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define SW shadow_who

/* Prototypes */
public int           eat_food(int amount, int ask);
public object        query_rotbloom_shadow();


/* 
 * Function name: eat_food
 * Description:   Eats a given amount of food
 * Arguments:     as eat_food() on /std/living.c
 * Returns:       Always 0 for non-wizards.
 */ 
int
eat_food(int amount, int ask)
{
    if (!ask)
    {
        SW->catch_tell("You feel so nauseated that the thought"
          + " of eating anything right now is completely intolerable. ");
    }

    return (SW->query_wiz_level() ? SW->eat_food(amount, ask) : 0);
}


/*
 * Function name:       query_rotbloom_shadow
 * Description  :       query the shadow
 * Returns      :       object -- this object
 */
public object
query_rotbloom_shadow()
{
    return this_object();
} /* query_rotbloom_shadow */


/*
 * Function name:        end_nausea
 * Description  :        remove the shadow from the player
 */
public void
end_nausea()
{
    SW->catch_tell("Feeling fresher air in your"
          + " nostrils, you are suddenly less nauseated.\n");
    remove_shadow();
} /* end_nausea */


/*
 * Function name:        begin_alarm
 * Description  :        set an alarm that will eventually
 *                       unshadow the player
 */
public void
begin_alarm()
{
    set_alarm(120.0, 0.0, end_nausea);
} /* begin_alarm */
