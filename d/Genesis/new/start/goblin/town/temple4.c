/*
 * File         : /d/Genesis/new/start/goblin/town/temple3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : October 6, 1999
 * Modifications: 
 * Purpose      : Temple of Xi Voch - Dome Walkway
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are upstairs in the Temple of Xi Voch");

    set_long("You are upstairs in the Temple of Xi Voch.\n" +
    "This narrow walkway encircles the large head of the statue " +
    "of Xi Voch. A small stone railing prevents you from falling " +
    "down into the chamber below. A stairway leads down from here.\n");

    add_item(({"statue", "head", "statue head", "xi voch",
    "head of xi voch", "head of statue"}),
    "From this vantage point, you confront the visage of Xi Voch at " +
    "extremely close range. The detail carved into the face is as " +
    "intricate as it is beautiful. The most noticeable feature is the " +
    "pair of shining red eyes which glow with an unnatural intensity.\n");

    add_item(({"eyes", "statue eyes", "eyes of statue",
    "eyes of xi voch", "red eyes"}),
    "The piercing red eyes of Xi Voch, the revered goblin god and saviour " +
    "of the Kalerians, seem to follow you as you move about on the walkway.\n");

    add_item(({"rail", "railing", "handrail", "hand rail"}),
    "The railing rises seamlessly from the stone of the walkway. The " +
    "entire room appears to have been carved from a single mass of " +
    "limestone.\n");

    add_item(({"stairs", "stairway"}),
    "The stone stairway leads down.\n");

    add_exit("temple3", "down");

    set_noshow_obvious(1);
}
