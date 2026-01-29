/*
 * /d/Gondor/common/lib/time.h
 *
 * This file will only contain the code that cannot be inherited and will
 * inherit that code that can be inherited. Since this code is included
 * almost all Gondorian rooms and in many rooms of the Shire, we should
 * make the code use as little memory as possible.
 *
 * /Mercade, 16 April 1994
 *
 * Revision history:
 */

inherit "/d/Gondor/common/lib/time.c";
#ifndef TIME
#define TIME 1

/*
 * Function name: init
 * Description  : This function links the command 'time' to each player
 *                in the room.
 */
public void
init()
{
    ::init();

    add_action(check_time, "time");
}
#endif
