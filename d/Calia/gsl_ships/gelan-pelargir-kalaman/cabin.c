/* Cabin for the ship from Calia to Krynn */

#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "ship.h"
#include <macros.h>

void
create_cabin()
{
        string labels = "The more interesting labels read as follows:\n " +
                    "Donut McCroissant's Pies/Pastries, " + 
                    "1 Million calories per cubic foot (gross estimate).\n" +
                    "Goldiloon's Assorted his and hers olde 'n hotte " +
                    "aphrodisiac potions (no liability accepted for: "  +
                    "hernias, heart attacks, unexpected rashes).\n" +
                    "Coiney Miser's authentic and exotic wares " +
                    "from all over the Genesis donut. No money back, " +
                    "guaranteed.\n" + 
                    "Patati Tomati's fresh fruit and veg, sell by " +
                     ctime(time()+100000) + " (me like be accurate " +
                    "about these things).\n";

	set_cabin_sound("Piles of boxes wave back and forth as the ship " +
                        "sways, looking like they're about to topple.\n"); 
	set_short("The floating walnut ship's cabin");
	set_long("You've descended belowdecks. Actually things are "+
		"pretty dark and dingy down here, but then what did you " +
                "expect for the inside of a walnut? You notice down here " +
                "that the ship tends to sway a lot, and you feel a little " +
                "queasy. You also notice "+
                "a lot of cargo stacked up in boxes against the walls, " +
                "and some of the labels appear to be interesting.\n");
        add_item(({"boxes", "cargo", "boxes of cargo"}), 
                   "There are very many boxes of cargo stacked down here, " +
                   "each with a label on it.\n");

        add_cmd_item(({"labels", "label"}), "read", labels); 
        add_item(({"labels", "label"}), labels);
               

	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS,1);
        add_prop(ROOM_I_HIDE, -1);
        add_prop(ROOM_I_NO_TELEPORT,1);
	add_exit(SHIPS+"deck.c", "up", 0,0);
}

