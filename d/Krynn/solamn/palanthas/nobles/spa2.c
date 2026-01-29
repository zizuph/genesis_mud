/* 
 * Laethorian Spa and Body, south of foyer
 *
 * Mortis 01.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_ROOMBASE;

string
query_to_jail()
{
  return "north";
}


void
reset_palan_room()
{

}

void
create_palan_room()
{
    SHORT("Intersection of halls in a dayspa");
    LONG("This hallway intersection is bright and clean with tall, silver "
	+ "braziers burning in each of its four corners.  The place is "
	+ "completely done in polished, translucent white marble.  The foyer "
	+ "is north, and the hallways continue in the remaining cardinal "
	+ "directions.\n");

	ITEM(({"spa", "dayspa"}), "The spa is quiet and clean.  Your footsteps "
	+ "echo down the hallways.  Have a <look> around.\n");
	ITEM("foyer", "The foyer is north of here is you wish to have another "
	+ "look.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling", "floor", "floors"}), "The walls and "
	+ "ceiling are of translucent white marble polished to a gleaming "
	+ "shine.\n");

    add_smell("vampire", "The air here is cool, clean, and flooded with "
	+ "scents subduing the scent of human blood.  The sterile odour of "
	+ "cleaning fluids, herbs, and stimulants is mild north.  From the west "
	+ "you pick up the smells of an indoor pool, and to the east you smell "
	+ "fragrant oils, and strong specialty soaps.  Further south, the air "
	+ "is moist and warm.");
    add_smell("morgul", "The air here is cool and clean.  The sterile odour "
	+ "of cleaning fluids, herbs, and stimulants is mild north.  From the "
	+ "west you pick up the smells of an indoor pool, and to the east you "
	+ "smell fragrant oils, and specialty soaps.  Further south, the air "
	+ "is moist and warm.");
    
	add_smell("human", "The air here is cool and clean.  From the north "
	+ "there is a mild sterile odour of recent cleaning mixed with the "
	+ "smells of invigorating herbal blends.  From the west you pick up "
	+ "the smells of an indoor pool, and to the east you smell fragrant "
	+ "oils, and specialty soaps.  Further south, the air is moist and "
	+ "warm.");
	add_smell("elf", "The air here is cool, clean, and fragrant.  The "
	+ "sterile odours of cleaning fluids mixed with the smells of a "
	+ "blend of stimulating, fresh herbs is to the north.  Your keen nose "
	+ "detects an indoor pool of water west and east the smells of "
	+ "fragrant oils, and specialty soaps.  Further south, the air is moist "
	+ "and warm.");
	add_smell("goblin", "The stink of mixed up herbs, harsh cleaning "
	+ "fluids, and dangerous soaps flood the cool air here.  Further south, "
	+ "the air is particularly moist and warm.");
	add_smell("dwarf", "The air here is cool and clean.  From the north "
	+ "there is a mild sterile odour of recent cleaning mixed with the "
	+ "smells of invigorating herbal blends.  From the west you pick up "
	+ "the smells of an indoor pool, and to the east you smell fragrant "
	+ "oils, and specialty soaps.  Further south, the air is moist and "
	+ "warm.");
	add_smell("hobbit", "Herbal blends from the north make your nose itch "
	+ "as you experience the cool, fragrant air here.  Also in the north "
	+ "there must be some serious cleaning going on judging by the sterile "
	+ "cleaning smells while from the west you think you pick up the "
	+ "smells of an indoor pool.  Fragrant oils, and specialty soap smells "
	+ "waft in from the east, and further south, the air is warm and moist.");
	add_smell("gnome", "The air here is cool and clean.  You detect "
	+ "quality, sterile cleaning fluids to the north mixed with herb "
	+ "stimulants.  To the west you believe you detect moisture "
	+ "indicative of an indoor body of water, and east fragrant oils "
	+ "commonly used by humans in massaging, and a variety of specialty "
	+ "soaps.  There must be more water south for the air there is warm and "
	+ "moist.");
	add_smell("minotaur", "Soapy, fragrant oils and odours designed to mask "
	+ "the scent of humans flood the cool, clean air here.  Harsh cleaning "
	+ "smells come from the north while to the west and south you detect "
	+ "moisture from an indoor pools.");
	add_smell("halfhuman", "The air here is cool and clean.  From the north "
	+ "there is a mild sterile odour of recent cleaning mixed with the "
	+ "smells of invigorating herbal blends.  From the west you pick up "
	+ "the smells of an indoor pool, and to the east you smell fragrant "
	+ "oils, and specialty soaps.  Further south, the air is moist and "
	+ "warm.");
	add_smell("halfelf", "The air here is cool and clean.  From the north "
	+ "there is a mild sterile odour of recent cleaning mixed with the "
	+ "smells of invigorating herbal blends.  From the west you pick up "
	+ "the smells of an indoor pool, and to the east you smell fragrant "
	+ "oils, and specialty soaps.  Further south, the air is moist and "
	+ "warm.");
	add_smell("orc", "The scent of manflesh tainted with herbal blends, "
	+ "harsh cleaning smells, and dangerous soaps floods your nostrils.  "
	+ "Further south, the air is warm and moist.");
	add_smell("hobgoblin", "The air here is clean and cool.  Common "
	+ "human sterilizing fluids come from the north mixed with the smells "
	+ "of stimulating herbal blends.  From the west you believe "
	+ "you smell an indoor pool, and east are fragrant soaps.  Further "
	+ "south, the air is warm and moist.");
	add_smell("kender", "Ahh!  The scents of exciting herbal blends waft "
	+ "in pleasantly from the north mixed with pungent sterile cleaning "
	+ "smells.  An odd mix that!  From the hall to the west you smell an "
	+ "indoor pool, and east are fragrant oils, and tantalizing soaps.  "
	+ "Further south, the air is warm and moist.  Human spas must be "
	+ "invigorating to investigate!");
	add_smell("drow", "The air here is refreshingly cool though a tad "
	+ "sterile due to the odours of cleaning fluids from the north mixed "
	+ "with the smells of stimulants and herbal blends.  To the west your "
	+ "keen nose detects the moisture from an indoor pool, and to the east "
	+ "you pick up fragrant oils, and human specialty soaps.  Further "
	+ "south, the air is moist and warm.");
	add_smell("noldor", "The air here is cool, clean, and fragrant.  The "
	+ "sterile odours of cleaning fluids mixed with the smells of a "
	+ "blend of stimulating, fresh herbs is to the north.  Your keen nose "
	+ "detects an indoor pool of water west and east the smells of "
	+ "fragrant oils, and specialty soaps.  Further south, the air is moist "
	+ "and warm.");

	EXIT(NOBLE + "spa", "north", 0, 0);
	EXIT(NOBLE + "spa_massage", "east", 0, 0);
	EXIT(NOBLE + "spa3", "south", "@@place_closed", 0);
	EXIT(NOBLE + "spa_pool", "west", 0, 0);
	
	reset_palan_room();
}

int
place_closed()
{
	write("To be opened in the near future.\n");
	return 1;
}