/*
 * cadu_p4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and added new exit to path to new Golbar camp, Treacher 08/2021
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("Small winding road");
    set_long("You are on a small winding road close to the centre of " +
             "Cadu. The crowd is getting thicker and thicker and you " +
             "can hardly move between all the people walking up and " +
             "down the street. The east side of the road is flanked by "+
             "some thick bushes.\n");
   
    add_item(({"people", "crowd"}),
             "As you carefully eye the people of Cadu, one " +
             "of them mutters something about strangers destructing the " +
             "moral of the youth.\n");
    add_item(({"Cadu", "centre of Cadu", "square", "big square", "buildings"}),
             "The centre of Cadu lies just north, and you notice a big "+
             "square with buildings all around.\n");
    add_item("road",
             "It's a small windling road where lots of people have travelled " +
             "between the bustling town centre and the pier. On the east " +
             "side of the road some thick bushes grow, blocking the view " +
             "in that direction.\n");
    add_item(({"bush", "bushes", "thick bush", "thick bushes"}),
             "The bushes are unexpectedly large, and thick. They could " +
             "easily conceal a hidden passage to the southeast. Actually now " +
             "when you think about it, you think it does!\n");
    add_item(({"passage", "hidden passage"}),
             "Just behind the first branches of the bushes someone has " +
             "cleared out a passage to the southeast through the bushes.\n");

   add_exit("cadu_q2", "north");
   add_exit("cadu_p3", "south");
   add_exit(CAMP + "room/path-n-0", "southeast", 0, 0, 1);
}
