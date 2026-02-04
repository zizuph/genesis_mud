/* garden21.c */
/* janus 920817 */
inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

create_room()
{
  set_short("garden gate");
  set_long(BS("You are in an opening in the hedge. Warm air can " +
	      "can be felt blowing in your face. Just to the south is an open " +
	      "ornate shining grating. To the north you can see an enormous " +
	      "garden.\n"));
  add_exit(JANUSDIR + "garden/garden1", "north",0);
  add_exit(JANUSDIR + "garden/entrance","south",0);
  add_item(({"hedge","large hedge"}), BS("A huge very well kept hedge. Must " +
			   "take forever to trim it. \n"));
  add_item(({"grating","gate"}), 
	   BS("The silvery grating seems " +
	      "to be of a very good workmanship. Unfortunately your grasp of " + 
	      "metallurgy isn't good enough to determine the material. The " + 
	      "gate seems to be locked in an half open position. " +
	      "In the middle of the gate is a wooden plaque. " + 
	      "Looking down you see that the ground is covered with a light "+ 
	      "grey gravel. Oddly enough there are no footprints where you" + 
	      " trod upon the gravel path. \n"));
  add_item(({"plaque","wooden plaque"}),
	   BS("It seems to be made of a dark shining wood. It is fastened to the " +
	      "grating with four silvery bolts. Since the plaque is facing the " +
	      "south direction you have to get to the other side to see the front of " + 
	      "the plaque. \n"));
  add_item(({"bolts","silvery bolts","bolt"}),
           BS("These are ordinary platinum bolts welded to the grate.\n"));
  add_item(({"gravel","footprints","ground"}),break_string("Looking closely"+
	   " at the gravel you see that each grain rolls back into its old " + 
	   "position after being moved. Awesome magic HUH ?.\n",70));
}
