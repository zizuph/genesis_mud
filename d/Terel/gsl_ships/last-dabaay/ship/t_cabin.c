#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

public void
create_room()
{
  ::create_shiproom();
  
    set_short("The captain's cabin");
    set_long("This elegant cabin bears the nautical look you would expect " +
	     "of its owner. On a writing desk in the corner you see " +
	     "scattered various instruments of navigation: maps, charts, " +
	     "sextant, and compass litter the fine teak surface. The rest " +
	     "of the room, however, is kept scrupulously neat.  Two odd " +
	     "circular windows, snugly framed in brass, look out over the " +
	     "rolling seascape.  A spyglass, a huge stuffed marlin, and a " +
	     "naval oil lamp are mounted on the starboard, aft, and port " +
	     "walls, respectively.\n");
    
    add_item("desk", "This fine teak desk must be worth a fortune; " +
	     "too bad it's bolted to the floor!\n");
    
    add_item(({"maps", "map", "chart", "charts"}),
	     "Most of the maps and charts seem to depict the sea " +
	     "lanes between Calathin and Sparkle.\n");
    
    add_item(({"sextant", "compass"}),
	     "It would hardly be the Captain's cabin without a sextant " +
	     "and compass, would it?\n");
    
    add_item("spyglass", "This beautifully made nautical instrument is " +
	     "firmly mounted to the wall and appears to be entirely " +
	     "decorative in purpose.\n");
    
    add_item(({"marlin", "fish"}),
	     "You have to admire the fisher who brought this trophy home!\n");
    
    add_item("window",
	     "Through the small circular port you see the ceaseless march " +
	     "of green waves.\n");
    
    add_item("lamp", "The bulbous oil compartment of this lamp is carefully " +
	     "designed to prevent spills.\n");
    
    add_prop(ROOM_I_INSIDE,1);
    add_exit(DECK, "fore", 0);
}
