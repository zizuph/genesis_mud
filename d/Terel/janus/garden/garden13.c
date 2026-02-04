/* garden13.c */
/* janus 930305 */
/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()


create_room()
{
  set_short("Stair");
  set_long(break_string("You are at the lower half of a narrow, "+
     "neat and steep white marble stair. Along the sides of the "+
     "stair there is a hedge, interspersed with small statues. \n",70));
  add_exit(JANUSDIR + "garden/garden12", "south",0);
  add_exit(JANUSDIR + "garden/garden14", "north",0);
  add_item(({"hedge"}),break_string("Looking closely "+
    "at the hedge you notice that it's about three yards high and "+
    "very compact. \n",70));
  add_item(({"statues","statue"}),BS("The statues depict "+
      "different strange beasts, none which you recognize. \n"));
}
