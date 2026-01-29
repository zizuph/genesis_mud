/* 
        Digit 02 FEB 95

	history:	2/2/95 		created by Digit
			11/2/95		descriptions added by Amelia
                        10/5/95         Direction changed, Maniac
                        22/5/95         temp block for shire pier
                      03/6/95     block removed...shire open
     
*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "road.h"

void
create_room()
{
	set_short("On the docks of Gelan");
	set_long("The docks are crowded now, as usual.  The noise and "+
		"colour are truly impressive.  Mingling with the sounds "+
		"of the crowd are the cries of seagulls, flying "+
		"around and occasionally landing on the water.  "+
		"You see crates and sacks stacked on the wharf, "+
		"awaiting shipment. To the west you see a pier " +
		"where a ship can dock.\n");

	add_item((({"crates", "sacks"})),
		("The piles of goods are tightly sealed so no one "+
		"can open them.  They bear interesting labels to "+
		"exotic places like FAERIE, MINAS TIRITH, and RE ALBI:  "+
		"REFNAS' CASTLE *HANDLE AT YOUR OWN RISK!!* ...\n"));
	add_item("seagulls", "The seagulls are as noisy as "+
		"the people, as they hunt for fish in the sea.\n");
	add_item((({"crowd", "colour"})),
		("There is a crowd of people moving about here, "+
		"all different races, wearing all kinds of "+
		"colourful clothing.  They are fairly noisy.\n"));
    add_exit(ROAD+"road20", "east", 0,0);
    add_exit(GSL_SHIP_DIR+"sparkle/pier", "west",0,0);
    add_exit(ROAD+"road22","north",0,0);
    add_exit(ROAD + "dock1", "southwest", 0, 0);
    
    reset_room();
}
