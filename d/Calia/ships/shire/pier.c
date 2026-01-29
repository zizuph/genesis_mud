
/* 
   Pier in Calia, for the Shire ship.

   Coded by Amelia.

   Changed for Shire by Digit, 16/5/95
   Modified by Maniac, June 1997
   Changed for the new ship system by Tapakah, 05/2009
*/

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

void
create_room()
{
  ::create_pier();
	set_short("A pier at the port of Gelan");
	set_long("The wooden pier extends out from the docks "+
		"and is clearly a place where ships land. There is "+
		"a large wooden post with ropes attached to it. "+
		"Between the cracks of the pier, you "+
		"look down and see water below.\n");


	add_item("water", "Just below the pier the water looks dark. "+
		"Hmmm...you can see a triangular-shaped fin moving "+
		"around down there. This doesn't look like a good place "+
		"to test your swimming skill.\n");
	add_item((({"post", "wooden post", "ropes"})),
		("There is a wooden post here with ropes wrapped "+
		"around it. It appears to be where boats are secured.\n"));
	add_item("cracks", "There are cracks in between the boards of the "+
		"pier, where you can look through and see the water below. "+
		"They are evenly spaced and very narrow, so there is no "+
		"danger of falling through, however.\n");
	add_item("view", "You can look out over the sea here, and "+
		"see seagulls and pelicans fishing the waves. There are "+
		"puffy white clouds over the horizon. The sea extends west "+
		"as far as you look in that direction.\n");
/*
    add_prop(ROOM_I_NO_CLEANUP,1);
	add_prop(OBJ_S_WIZINFO, "To restart the ship, ONLY if it "+
		"is stuck, type 'Call here restart_ship <reason>'.\n");
*/

    add_exit("/d/Calia/mountain/road/road22","east",0,0);

    add_pier_entry(MASTER_OB(TO), "Gelan", "Kalaman - Pelargir Circle");
	initialize_pier();
}
