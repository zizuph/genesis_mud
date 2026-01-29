/* Pier in Calia, for the Khalakhor ship.

   Based mainly on Amelia's pier.
   Coded by Maniac. 27/11/95
    Changed for Khalakhor by Jaacar.  6/09/97
*/

#pragma save_binary

inherit "/std/room";
#include "ship.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("A wooden pier at the port of Gelan");
    set_long("The pier extends out from the docks and is clearly a "+
        "place where ships land. This one does not appear to be used "+
        "very much, and is constructed of wooden planks. The pier itself "+
        "is not very high above the water. You conclude it must be a "+
        "fairly small boat that docks at this pier. The sea stretches out "+
        "to the horizon to your west.\n");

        add_item("horizon", "It's pretty far away, Genesis is huge.\n");

        add_item("pier", "You're standing on it.\n");
	add_item("water", "Just below the pier the water looks dark. "+
		"Hmmm...you can see a triangular-shaped fin moving "+
		"around down there. This doesn't look like a good place "+
		"to test your swimming skill.\n");
	add_item(({"view", "sea"}), "You can look out over the sea here, and "+
		"see seagulls and pelicans fishing the waves. There are "+
		"puffy white clouds over the horizon. The sea extends west "+
		"as far as you look in that direction.\n");

	add_exit("/d/Calia/mountain/road/road26", "north");
}

