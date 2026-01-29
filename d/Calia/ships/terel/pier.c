/* Pier in Calia, for the Krynn ship.

   Based mainly on Amelia's pier.
   Coded by Maniac. 27/11/95
   Ship disabled until double service is implemented, Tapakah, 05/2009
   Now used by Circle Line, Tapakah, 31/05/2009
*/

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
create_room()
{
	set_short("A crystalline pier at the port of Gelan");
	set_long("The pier extends out from the docks "+
	    "and is clearly a place where ships land. This " +
            "one is special, made of smooth, flawless crystal, " +
            "a material from which those under the instruction " +
            "of Caliana are able to build mighty structures, both " +
            "elegant and strong. The sea stretches out to the horizon " +
            "to your west.\n");

        add_item("crystal", "The crystal that the pier is made of is " +
             "perfectly cut, and by its unusual light refraction it seems " +
             "likely that it is enchanted.\n");

        add_item("horizon", "It's pretty far away, Genesis is huge.\n");

        add_item("pier", "You're standing on it.\n");
	add_item("water", "Just below the pier the water looks dark.  "+
		"Hmmm...you can see a triangular-shaped fin moving "+
		"around down there. This doesn't look like a good place "+
		"to test your swimming skill.\n");
	add_item(({"view", "sea"}), "You can look out over the sea here, and "+
		"see seagulls and pelicans fishing the waves. There are "+
		"puffy white clouds over the horizon. The sea extends west "+
		"as far as you look in that direction.\n");

	add_exit("/d/Calia/mountain/road/road24", "east");
    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();
    add_pier_entry(MASTER_OB(TO), "Gelan", "Pan-Donut Circle");
    initialize_pier();
}

object
query_sign ()
{
  return sign;
}
