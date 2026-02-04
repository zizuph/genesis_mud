/* garden14.c */
/* janus 930305 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()


create_room()
{
  object door;
  set_short("Stair");
  set_long(break_string("You are at the top of a narrow, "+
     "neat, steep, white, and marble stair. Along the sides of the "+
     "stair there is a hedge, interspersed with small statues. \n",70));
  add_exit(JANUSDIR + "garden/garden13", "south",0);
  add_item(({"hedge"}),break_string("Looking closely "+
    "at the hedge you notice that it's about three yards high and "+
    "very compact. \n",70));
  add_item(({"statues","statue"}),BS("The statues depicts "+
      "different strange beasts, none which you recognize. \n"));
  add_item(({"stair","marble stair"}),BS("It is made out of white polished "+
             "marble. \n"));
  door = clone_object(JANUSDIR + "garden/stair_door");
  door -> move(this_object());
}
