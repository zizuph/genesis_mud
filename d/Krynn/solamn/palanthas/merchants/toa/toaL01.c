/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string dsmell = "The air is moist here with a hint of mildew. ";
object tdoor;

string
query_to_jail()
{
    return "north";
}

void
create_palan_room()
{
    SHORT("The central room in the dungeon of the Tower of Arms");
    LONG("Marble corridors extend through the tower dungeon from here. "
    + "Shadows flicker, and the sound of water dripping can be heard nearby. "
    + "An iron door is recessed into the east wall.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toaL02", "north", 0, 0);
    EXIT(TOA + "toaL03", "south", 0, 0);
    EXIT(TOA + "toaL04", "west", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_stores_door1");
    tdoor->move(TO);

    add_smell("vampire", dsmell + "Your heightened sense of smell "
    + "picks up the scent of a mildewy jail to the west and armament oil "
    + "through the door to the east.");
    add_smell("morgul", dsmell + "The familiar stink of jail cells wafts "
    + "from the west. Metal smells seep through the door to the east.");
    
    add_smell("human", dsmell + "Is there also some pee or something down "
    + "here?");
    add_smell("elf", dsmell + "Human stink is strong here. You smell "
    + "weapons through the door to the east.");
    add_smell("goblin", dsmell + "It smells familiar down here.");
    add_smell("dwarf", dsmell + "The familiar scents of weapons, armour, "
    + "and leather are strong through the eastern door.");
    add_smell("hobbit", dsmell + "It stinks down here frankly.");
    add_smell("gnome", dsmell + "You smell human jail cells west and some "
    + "sort of metal smells east.");
    add_smell("minotaur", dsmell + "The smell of human flesh floods "
    + "your senses.");
    add_smell("halfhuman", dsmell + "Does it smell like pee here?");
    add_smell("halfelf", dsmell + "Does it smell like pee here?");
    add_smell("orc", dsmell + "The smell of dirty manflesh is strong here, "
    + "and the distinct tang of armaments are through the door east.");
    add_smell("hobgoblin", dsmell + "The distinct tang of weapons and "
    + "armour are through the eastern door.");
    add_smell("kender", dsmell + "It does not smell like candy here. Maybe "
    + "pee pee a little.");
    add_smell("drow", dsmell + "Sar'elgg! It's mildewy to the west and "
    + "filthy. Metal and leather scents come from behind the eastern door.");
    add_smell("noldor", dsmell + "Humans have been kept down here in the "
    + "overly moist air for long periods of time. How unpleasant.");
}

void
auto_door()
{
    tdoor->reset_door();
}
