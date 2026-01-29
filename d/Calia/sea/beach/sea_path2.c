/*
*	coder(s): Amelia
*       history: coded 5/5/95
*
*    Minor alterations by Maniac  18/8/96
*/


#pragma save_binary

inherit "/d/Calia/std/room_tell_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
	set_short("A sand dune");
	set_long("The dune is fairly steep here. As you walk along, "+
		"your feet sink into soft white sand. Not much grows "+
		"here except occasional sea grass. At a distance to "+
		"the northeast, the impressive gates and towers of Gelan "+
		"shine brightly in the sun. To the east you see a "+
		"road which begins at Gelan and cuts through the "+
		"purple moorland to the southeast.\n");

	add_item((({"grass", "sea grass", "pampas grass"})),
		("Graceful fronds of sea grass sway gently in "+
		"the breezes. Here and there you see pampas grass, "+
		"with it's tall stalks topped with white tassels.\n"));
	add_item((({"moorland", "purple moorland"})),
		("To the south the landscape turns into rolling "+
		"hills covered with a purplish vegetation. It looks "+
		"somewhat mysterious and barren.\n"));
	add_item((({"dune", "dunes","sand dune", "sand dunes"})),
		("The dune is a large hill of white sand.  The sand "+
		"seems to shift in the wind making interesting "+
		"patterns.  You are almost at the top, and it's fairly "+
		"steep here.\n"));

	add_item((({"sand", "white sand"})),
		("The sand is as white as sugar, but it's "+
		"somewhat difficult to walk in.\n"));
	add_item((({"city", "Gelan"})),
		("Gelan looks to be a large, well-fortified city. "+
		"From here you see its towers, white walls, and "+
		"impressive gates.\n"));
	add_item((({"gates", "towers", "impressive gates", "walls"})),
		("The city of Gelan is fortified with great "+
		"stone walls, towers, and gates.\n"));
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);

	add_exit(BEACH+"sea_path1", "east", 0,0);
	add_exit(BEACH+"sea_path3", "west", 0,5);
}
