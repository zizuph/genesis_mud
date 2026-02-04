/* garden22.c */
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
  set_short("Orangery entrance");
  set_long(break_string("The path ends in front of a large glass "+
     "building. There is a small glass door in the wall, there "+
      "is a small sign on the door.\n",70));
  add_exit(JANUSDIR + "garden/garden12", "east",0);
  add_cmd_item(({"sign","small sign"}),({"read","exa"}),
         ({"@@do_sign","@@do_sign"}));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH? \n",70));
  add_item(({"orangery","glass building"}),BS("The house "+
     "is about 6 meters high and completely covered with glass. "+
     "It's not possible to see anything since the air inside the building is "+
     "very humid and therefore water has "+
     "condensed on the window and is blocking the view. \n"));
  door = clone_object(JANUSDIR  + "garden/orangery_door");
  door -> move(this_object());

}
do_sign()
{
    return ("On the sign you read the following scribbled text: \n" +
   " The Orangery will open as soon as "+
    "things are in order. \n");
}

