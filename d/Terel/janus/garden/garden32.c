/* garden32.c */
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
  set_short("Greenhouse entrance");
  set_long(break_string("The path ends in front of a large glass "+
     "building. There is a small glass door in the wall. \n",70));
  add_exit(JANUSDIR + "garden/garden12", "west",0);
  /*    add_exit(JANUSDIR + "garden/labyrinth1", "west",0); */
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH? \n",70));
  add_item(({"building","glass building","greenhouse"}),BS("The house "+
     "is about 6 meters high and completely covered with glass. "+
     "It's not possible to see anything since the air inside the building is "+
     "very humid and therefore water has "+
     "condensed on the window and is blocking the view. \n"));
  door = clone_object(JANUSDIR + "garden/ghouse_door");
  door -> move(this_object());
}
