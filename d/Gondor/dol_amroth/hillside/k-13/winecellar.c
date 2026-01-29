/*
 * hall4.c
 *
 * Skippern 20(c)02
 *
 * The cellar.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <macros.h>

/* Prototypes */

/* Code */

void
create_inside()
{
    set_short("a wine cellar");
    set_long("A wine cellar with loads of barrels and flasks filled with " +
	     "wine.\n");
	set_long("This cellar is dark and gloomy. Small oil lamps put on holders on the " +
		"walls give little illuminance, but enough to find your way around the narrow " +
		"corridors between racks of wine bottles, flasks, and barrels. The air in here " +
		"is slightly chilly and damp, which is ideal for storing wine over longer " +
		"periods. Dust cover most surfaces, and many of the bottles are covered with " +
		"spiders webs.\n");
		
	add_item( ({ "lamp", "lamps", "oil lamp", "oil lamps" }), "Small oil lamps placed " +
		"on holders on the walls provides a little gloomy illuminance. These lamps " +
		"are designed to burn the oil slowly giving enough light to find your way " +
		"without producing any significant heat. The glass bobble under the flame is " +
		"designed so that they can be filled with oil without extinguishing the flame.\n");
	add_item( ({ "barrel", "barrels", "cask", "casks" }), "Large barrels a containing " +
		"wine are stacked up several places in the cellar. All the barrels are laying " +
		"with the flat headboard facing out. Some barrels have obviously been prepared " +
		"for consume with a small tap mounted on the headboard. Other barrels have a " +
		"cork on the top where a glass staff can be entered to take a sample. The barrels " +
		"looks old, most of them have a layer of dust over them, and some do even have " +
		"some spiders web attached between them and other barrels.\n");
	add_item( ({ "bottle", "bottles", "flask", "flasks" }), "Inserted into racks, with the " +
		"bottoms faced out are bottles and flasks containing wine. Some empty bottles are " +
		"stored in a crate in the corner. The bottles have lables identifying their origens " +
		"and vintages. The bottles themselves are of any size, shape and colour.\n");

    add_exit(DOL_HILLS + "k-13/hall1", "up", 0, 1);

}

init()
{
    ::init();
}

