inherit "/std/room.c";

#include <ss_types.h>
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()


void
create_room()
{
	set_short("Lennox #37"); /* This will show up when the player is in */
                               /* "brief" mode.                           */
	/* Set the long description of the room */
	set_long(break_string(
	  "The whitewashed walls slant up to form a point above your head "
	+ "as you gaze down the length of this oddly formed room. Through "
	+ "the clover-shaped window at the end the sound of singing birds "
	+ "wafts gently in with the sweet air of a Terelian summer. Hardwood "
	+ "floors creak under your feet with every step. Frisbees litter the "
	+ "room and a pair of rollerblades sits by the neatly made bed.\n",70));

	add_exit("/d/Genesis/start/human/town/church", "south", 0, 1);
	add_exit(MANSION + "library/library_1","window",0,1);

	add_item(({ "rollerblades", "blades", "skates"}), break_string(
	  "Properly speaking, these should not be here at all...they're hardly "
	+ "medieval! But hopefully no one but Cedric will ever see them, and "
	+ "anyway Cedric is only using them to learn how to program LPC. Don't "
	+ "even try to pick these up; they are strictly scenery.\n",70));
	
	 add_item(({ "frisbees", "frisbee", "disk"}), break_string( 
	  "There are many frisbees in this room, and though Cedric would have "
	+ "you believe that he won them all at regional, sectional, and national " 
	+ "tournaments, the truth is he bought most of them.\n",70));

	add_item(({"window"}),"Jumping out will take you to Cedric's current project rooms.\n");

	add_prop(ROOM_I_INSIDE, 1);	/* indoors room */
}