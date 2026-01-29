/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string dsmell = "The air is damp here with a smell of weapon oil. ";

string
query_to_jail()
{
  return "north";
}

object nchest;

void
reset_palan_room()
{
    nchest->reset_container();
}

void
create_palan_room()
{
    SHORT("A store room in the dungeon of the Tower of Arms");
    LONG("Extra pegs and shelving for armaments and gear line the walls here. "
    + "Shadows flicker, and the sound of water dripping can be heard nearby."
    + "\n");

    ITEM(({"peg", "pegs", "shelf", "shelves", "shelving"}), "Although there "
    + "is no extra gear being stored in this room, there are plenty of pegs, "
    + "and shelves for storing it neatly.\n");

    EXIT(TOA + "toa_store01", "north", 0, 0);

    add_smell("vampire", dsmell + "Your heightened sense of smell "
    + "picks up the scent of a mildewy jail to the west and weapon oil "
    + "close by.");
    add_smell("morgul", dsmell + "The familiar stink of jail cells wafts "
    + "from the west. Metal smells seep throughout this area.");
    
    add_smell("human", dsmell + "You smell metal and oil.");
    add_smell("elf", dsmell + "Human stink is strong here. You smell "
    + "weapons throughout the area.");
    add_smell("goblin", dsmell + "It smells familiar down here.");
    add_smell("dwarf", dsmell + "The familiar scents of weapons, armour, "
    + "and leather are strong throughout the area.");
    add_smell("hobbit", dsmell + "It stinks down here frankly.");
    add_smell("gnome", dsmell + "You smell human jail cells west and some "
    + "sort of metal around this store room.");
    add_smell("minotaur", dsmell + "The smell of human flesh floods "
    + "your senses, but you also smell weaponry.");
    add_smell("halfhuman", dsmell + "Does it smell like pee here?");
    add_smell("halfelf", dsmell + "Does it smell like pee here?");
    add_smell("orc", dsmell + "The smell of dirty manflesh is strong here, "
    + "and the distinct tang of armaments are strong nearby.");
    add_smell("hobgoblin", dsmell + "The distinct tang of weapons and "
    + "armour are strong nearby.");
    add_smell("kender", dsmell + "It does not smell like candy here. Maybe "
    + "pee pee a little, maybe metal.");
    add_smell("drow", dsmell + "Sar'elgg! It's mildewy to the west and "
    + "filthy. Metal and leather scents come from all over this area.");
    add_smell("noldor", dsmell + "Humans have been kept down here in the "
    + "overly moist air for long periods of time. How unpleasant. It smells "
    + "of armaments close by, also.");

    nchest = clone_object(TOA + "obj/toa_store_wpn_rack");
    nchest->move(TO);

    reset_palan_room();
}
