/* A magical full plate armour worn by Verminaard
 *
 * Blizzard, 15.07.2003
 *
 * Navarre October 2010. Changing the colour to be random.
 *                       The original idea was to have one of 
 *                       each of the colors available in the 
 *                       game, but that's just way too much.
 *                       So we change this to be random colour.
 *                       The adjectives of the armour itself,
 *                       doesn't change with color.
 */
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/common/armours/fullplate";

string *colors = ({"red", "blue", "green", "black", "white"});

void
create_fullplate()
{
    set_color(ONE_OF(colors));
}
