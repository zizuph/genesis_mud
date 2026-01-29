/*
 *  /d/Emerald/common/guild/aod/obj/ogrestomp_shadow.c
 *
 *  This is the shadow that is added to rooms where an Ogre has used
 *  the ogrestomp. It prevents players from using room exits for a
 *  few seconds.
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/shadow";

/* Global Variables */
public float      Delay = 15.0;

/* Prototypes */
public void       remove_ogrestomp_shadow();

public void       set_stomp_delay(float f) { Delay = f; }
public int        query_ogrestomp_shadow() { return 1; }


/*
 * Function name:        remove_ogrestomp_shadow
 * Description  :        We want to immediately start the countdown
 *                       to destruct the shadow. However, we want
 *                       the count to be varied, based on how good
 *                       the ogrestomp was. We therefore base the
 *                       delay on the float that is set at creation.
 */
public void
remove_ogrestomp_shadow()
{
    set_alarm(Delay, 0.0, "remove_shadow");
} /* remove_ogrestomp_shadow */


/*
 * Function name: exit_move
 * Description:   Invoke the move routine which sends the actor through the
 *                exit into the next room. Basically it is a relay allowing
 *                coders to intercept the actual person->move_living() call.
 * Arguments:     string exit_cmd - the exit command, as provided to add_exit()
 *                object dest_room - the destination room
 * Returns:       int - the result of the move_living() call.
 */
/*
public int
exit_move(string exit_cmd, object dest_room)
{
    this_player()->catch_tell("The ground is shaking too much right"
      + " now. Your feet can't manage it!\n");
    return 7;
} exit_move */


/*
 * Function name: unq_move
 * Description  : This function is called when a player wants to move through
 *                a certain exit. VBFC is applied to the first and third
 *                argument to add_exit(). Observe that if you have a direction
 *                command that uses its trailing test as in 'enter portal'
 *                and fails if the second word is not 'portal', your block
 *                function should return 2 as you want the rest of the dir
 *                commands to be tested.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0.
 */
public int
unq_move(string str)
{
    notify_fail("The ground is shaking too much right now. Your feet"
      + " can't manage it!\n");
    return 0;
} /* unq_move */