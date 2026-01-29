/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

object rat;

void
reset_room()
{
   if(rat)
       return;
   tell_room(this_object(), "A rat comes crawling from the hole.\n");
   rat = clone_object(S_LOCAL_NPC_DIR + "ratty");
   rat->move(TO);
}

void
create_room()
{
    set_short("Fortress hall");
    set_long("You stand within the last part of this damp corridor. To\n"
             + "your north is a doorframe with no door. On the wall directly\n"
             + "to your left is a small hole. The ceiling gets lower here,\n"
             + "but you are still able to stand.\n");
    add_item(({"doorframe", "frame"}),
             break_string("You are looking at a crooked door frame that "+
                          "does not have a door in it. You think you hear "+
                          "some noises just north of it.\n", 70));
    add_item(({"wall"}),
             break_string("It is a rough wall with a hole near the bottom "+
                          "of it.\n", 70));
    add_item(({"hole", "small hole"}),
             break_string("This is a small hole just large enough for "+
                          "vermin to scrape through.\n", 70));
    add_item(({"ceiling", "up"}),
             break_string("The ceiling gradually slopes downward.\n", 70));

    add_prop(ROOM_I_INSIDE, 1);
    add_exit("hall2", "south");
    add_exit("guardroom", "north");

    reset_room();
}

