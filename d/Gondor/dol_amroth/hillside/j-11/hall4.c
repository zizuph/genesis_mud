/*
 * hall4.c
 *
 * Skippern 20(c)02
 *
 * The kitchen.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <macros.h>

/* Prototypes */

/* Code */

void
create_inside()
{
    set_short("a kitchen");
    set_long("Inside a well equiped and busy kitchen. Servants are " +
		"running to and from carrying ingredients, and finished meals. " +
		"There are a huge stove in the center of the room, and on one " +
		"of the walls a huge stonecovered fireplace, of the type where " +
		"you can bake bread. Pots and pans of various sizes hang from " +
		"beams under the ceiling, which itself is black of sooth.\n");
	
	add_item( ({ "stove", "huge stove" }), 
		"A huge stove occupies the center of the room. " +
		"It is made of black cast-iron, stand on legs looking like " +
		"the legs of some sort of fable animal, and is wood fired. " +
		"It looks very hot, and some pans are sizzling on a few of " +
		"the eight cookingplates.\n");
	add_item( ({ "fireplace", "huge fireplace", "stonecovered fireplace",
		"huge stonecovered fireplace" }),
		"A huge stonecovered fireplace is located on one of the walls. " +
		"The thick granite slabs making up the walls of the fireplace is " +
		"heated by burning off wood inside it, and after cleaning out the " +
		"ashes can be used to bake bread, or other culinary activities. " +
		"It looks capable of staying hot for hours.\n");
	add_item( ({ "pot", "pots", "pots and pans", "pans", "pan" }),
		"Pots and Pans of all imaginable size hangs from beams in the " +
		"ceiling. Most of them are common pots or pans in a reddish coloured " +
		"metal, though some seem to be made of some more exotic material, " +
		"maybe used for special occations.\n");
	add_item("ceiling", "The ceiling is black with sooth, after decades of " +
		"service in the kitchen. Beams under the ceiling is used to store " +
		"pots and pans of various sizes.\n");

    add_exit(DOL_HILLS + "j-11/hall1", "northeast", 0, 1);

}

init()
{
    ::init();
}

