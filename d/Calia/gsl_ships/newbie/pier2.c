/*
 * Pier in Gelan
 *
 * Serves the Newbie Line:
 *   Gelan - Sparkle - Port Macdunn - Grey Havens
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>      
#include <macros.h>                                             
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

public void
create_pier()
{
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

    setuid();
    seteuid(getuid());
    
	add_exit("/d/Calia/mountain/road/dock2", "south");

    add_pier_entry(MASTER_OB(this_object()), "Gelan", "Newbie Pier to Sparkle");
}
