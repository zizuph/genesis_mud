/* Mortis 9.2014
 * Replace visible "down" exit with something interesting.
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string dsmell = "The air is moist here with a hint of mildew. ";

string
query_to_jail()
{
    return "northeast";
}

void
create_palan_room()
{
    SHORT("A jail cell in the dungeon of the Tower of Arms");
    LONG("This large cell is well made for a jail. It is currently empty. "
    + "Shadows flicker, and the sound of water dripping can be heard nearby. "
    + "Dusty footprints are scattered about the cell.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");
    ITEM(({"jail", "jail cells", "cell", "cells"}), "Iron barred jail cells "
    + "stand open to your northwest, west, and southwest. Their doors are "
    + "locked open in inuse at the moment.\n");
    ITEM(({"dusty footprints", "footprints", "footprint"}), "Despite this "
    + "jail not appearing to be in use at the moment, there are a lot of "
    + "dusty footprints around, especially around the southwest corner.\n");
    ITEM(({"southwest corner", "sw corner", "corner"}), "The southwest "
    + "corner has a block that pushes in! It reveals a staircase going "
    + "down into pitch-black darkness.\n");

    EXIT(TOA + "toaL04", "northeast", 0, 0);
	add_invis_exit(UTOA + "utoa01", "down", 0, 0);

    add_smell("vampire", dsmell + "Your heightened sense of smell "
    + "picks up the scent of a mildewy jail to the west and armament oil "
    + "back through the door to the east.");
    add_smell("morgul", dsmell + "The familiar stink of jail cells wafts "
    + "from the west. Metal smells seep through the door back to the east.");
    
    add_smell("human", dsmell + "Is there also some pee or something down "
    + "here?");
    add_smell("elf", dsmell + "Human stink is strong here. You smell "
    + "weapons through the door back to the east.");
    add_smell("goblin", dsmell + "It smells familiar down here.");
    add_smell("dwarf", dsmell + "The familiar scents of weapons, armour, "
    + "and leather are strong through the eastern door down the corridor.");
    add_smell("hobbit", dsmell + "It stinks down here frankly.");
    add_smell("gnome", dsmell + "You smell human jail cells west and some "
    + "sort of metal smells east.");
    add_smell("minotaur", dsmell + "The smell of dirty human flesh floods "
    + "your senses.");
    add_smell("halfhuman", dsmell + "Does it smell like pee here?");
    add_smell("halfelf", dsmell + "Does it smell like pee here?");
    add_smell("orc", dsmell + "The smell of dirty manflesh is strong here, "
    + "and the distinct tang of armaments are back through the door east.");
    add_smell("hobgoblin", dsmell + "The distinct tang of weapons and "
    + "armour are through the eastern door down the corridor.");
    add_smell("kender", dsmell + "It does not smell like candy here. Maybe "
    + "pee pee a little.");
    add_smell("drow", dsmell + "Sar'elgg! It's mildewy to the west and "
    + "filthy. Metal and leather scents come from behind the eastern door "
    + "back down the corridor east.");
    add_smell("noldor", dsmell + "Humans have been kept down here in the "
    + "overly moist air for long periods of time. How unpleasant.");
}
