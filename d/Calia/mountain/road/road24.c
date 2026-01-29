/* 
        road leading to pier for Calia-Terel ship.

	history:	
                  copied over from another pier road    Maniac  28/11/95
     
*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "road.h"


object sign;

void
reset_room()
{
  ::reset_room();
  return;
	seteuid(getuid(TO));
	if (!objectp(sign))
	{
        sign = clone_object(SHIP_DIR+"terel/sign.c");
		sign->move(TO);
	}
}


void
create_room()
{
	set_short("On the docks of Gelan");
	set_long("The docks are crowded now, as usual.  The noise and "+
		"colour are truly impressive.  Mingling with the sounds "+
		"of the crowd are the cries of seagulls, flying "+
		"around and occasionally landing on the water.  "+
		"You see crates and sacks stacked on the wharf, "+
           "awaiting shipment.  West of here, on a pier, you notice a sign.\n");

	add_item((({"crates", "sacks"})),
		("The piles of goods are tightly sealed so no one "+
		"can open them.\n"));
	add_item("seagulls", "The seagulls are as noisy as "+
		"the people, as they hunt for fish in the sea.\n");
	add_item((({"crowd", "colour"})),
		("There is a crowd of people moving about here, "+
		"all different races, wearing all kinds of "+
		"colourful clothing.  They are fairly noisy.\n"));
//  add_exit(ROAD+"road25","north",0,0); /* Closed for now - Gorboth */
	add_exit(ROAD+"road23", "south", 0,0);
        add_exit(SHIP_DIR+"terel/pier","west",0,0);
	reset_room();
}
