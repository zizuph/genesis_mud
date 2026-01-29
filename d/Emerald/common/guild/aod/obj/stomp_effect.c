/*
 *  /d/Emerald/common/guild/aod/obj/stomp_effect.c
 *
 *  This is the object that is cloned into a room when Ogres use the
 *  <ogrestomp> command. It prevents people from leaving the room
 *  for a brief period of time. To prevent people from making
 *  a room permenantly inescapable, the effect produces diminishing
 *  returns if used repeatedly.
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 *
 *    Credit for the mechanics of this effect goes to the
 *    inestimably helpful and much appreciated Mercade.
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <filter_funs.h>
#include <stdproperties.h>

/* Global Variables */
public float       Delay;         /* the duration of the effect     */
public int         Prolonged = 0; /* has the effect been prolonged? */

/* Prototypes */
public void        create_object();
public int         block_exit(string str);
public void        init();
public void        remove_stomp_effect();
public void        remove_ogrestomp_object(float delay);

public float       query_delay() { return Delay; }
public void        set_prolonged() { Prolonged++; }


/*
 * Function name:        create_object
 * Description  :        The constructor for the object
 */
public void
create_object()
{
    set_name(AOD_OGRESTOMP_EFFECT);

    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, "Get what from where?\n");
} /* create_object */


/*
 * Function name:        block_exit
 * Description  :        make it impossible to leave the room
 *                       right now
 * Arguments    :        string str - the direction typed
 * Returns      :        int 1: we do not allow passage
 */
public int
block_exit(string str)
{
    write("Your legs can't manage with the earthquake! Wait till it"
        + " subsides.\n");
    return 1;
} /* block_exit */


/*
 * Function name:        init
 * Description  :        add actions to the player to block the
 *                       use of room exits
 */
public void
init()
{
    string *exits = environment()->query_exit_cmds();

    if (!environment()->query_prop(ROOM_I_IS) || !sizeof(exits))
    {
        return;
    }

    foreach(string exit: exits)
    {
        add_action(block_exit, exit);
    }
} /* init */


/*
 * Function name:        remove_stomp_effect
 * Description  :        remove the effect, alert the room that the
 *                       ground has stopped shaking
 */
public void
remove_stomp_effect()
{
    int     i,
            n = 0;
    float   f = 0.0;
    object *stuff_in_room = FILTER_DEAD(all_inventory(environment(
                            this_object())));

    TELL_G("remove_stomp_effect called!\n");

    if (Prolonged)
    {
        TELL_G("Prolonged = true!");
        for (i = 0; i < Prolonged; i++)
        {
            Delay = Delay / 2.0;
            f += Delay;
            TELL_G("Prolonged by " + ftoi(Delay));
        }

        Delay = f;
        Prolonged = 0;
        TELL_G("New Delay = " + ftoi(Delay));
        set_alarm(Delay, 0.0, remove_stomp_effect);

        return;
    }

    TELL_G("Prolonged = false!");

    for (i = 0; i < sizeof(stuff_in_room); i++)
    {
        if (stuff_in_room[i]->id(AOD_OGRESTOMP_EFFECT))
        {
            n++;
        }
    }

    if (n < 2)
    {
        tell_room(environment(this_object()), "The earthquake"
          + " subsides, and you regain your footing.\n");
    }

    remove_object();
} /* remove_stomp_effect */


/*
 * Function name:        remove_ogrestomp_object
 * Description  :        We want to immediately start the countdown
 *                       to destruct the object. However, we want
 *                       the count to be varied, based on how good
 *                       the ogrestomp was. We therefore base the
 *                       delay on the float that is set at creation.
 */
public void
remove_ogrestomp_object(float delay)
{
    Delay = delay;
    set_alarm(delay, 0.0, remove_stomp_effect);
} /* remove_ogrestomp_object */