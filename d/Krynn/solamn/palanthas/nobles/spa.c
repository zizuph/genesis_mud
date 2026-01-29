/* 
 * Laethorian Spa and Body
 *
 * Mortis 01.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit NOBLE_ROOMBASE;

#define VIEWNORTH			(NOBLE + "nplaza")

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
    SHORT("Laethorian Spa and Body");
    LONG("The foyer of the Laethorian dayspa is bright and clean with "
	+ "tall, silver braziers burning in each of its four corners.  The "
	+ "place is completely done in polished, translucent white marble.  On "
	+ "the floor is an eight pointed pinwheel pattern mosaic done in "
	+ "gleaming, enameled black tiles.  A marble pedestal by the door "
	+ "displays a sign etched into its angled top.\n");

	ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
	+ "pleasurable services in the nobles quarter.  You can view it from "
	+ "the windows north.\n");
	ITEM(({"spa", "dayspa"}), "The spa is quiet and clean.  Your footsteps "
	+ "echo in the foyer.  Have a <look> around.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling"}), "The walls and ceiling are of "
	+ "translucent white marble polished to a gleaming shine.\n");
	ITEM(({"floor", "floors", "pattern", "mosaic", "pinwheel"}), "A large "
	+ "mosaic covers the polished, translucent white marble floor, a "
	+ "pinwheel pattern seemingly spiraling in motion counter-clockwise.  "
	+ "It has eight points and is done in small, square, enameled black "
	+ "tiles polished to a gleaming shine.  There's something soothing "
	+ "about gazing at it.\n");
	ITEM(({"tile", "tiles", "enameled black tiles", "black tiles",
		"enameled tiles"}), "Small, square tiles with a gleaming, enameled "
	+ "black finish create an elusive pattern upon the floor.\n");
	ITEM(({"sign", "pedestal", "top"}), "A meter and a half tall, marble "
	+ "pedestal stands by the doorway, its top surface angled to be easily "
	+ "viewed by visitors.  Upon it, chiseled in the old style, is a sign.\n");

    add_smell("vampire", "The air here is cool, clean, and flooded with "
	+ "scents subduing the scent of human blood.  The sterile odour of "
	+ "cleaning fluids is strong east.  From the west you detect blends of "
	+ "herbs and stimulants, and to the south your keen senses pick up the "
	+ "smells of an indoor pool, fragrant oils, and strong specialty soaps.");
    add_smell("morgul", "The air here is cool and clean.  From the east "
	+ "there is a very sterile odour of recent cleaning while to the west "
	+ "you pick up the smells of stimulants and herbal blends.  From the "
	+ "hall to the south, you think you smell an indoor pool, fragrant "
	+ "oils, and specialty soaps.");
    
	add_smell("human", "The air here is cool and clean.  From the east there "
	+ "is a very sterile odour of recent cleaning while to the west you pick "
	+ "up the smells of invigorating herbal blends.  From the hall to the "
	+ "south, you think you smell an indoor pool, fragrant oils, and "
	+ "specialty soaps.");
	add_smell("elf", "The air here is cool, clean, and fragrant.  The "
	+ "sterile odours of strong cleaning fluids come from the east while "
	+ "to the west come the smells of a blend of stimulating, fresh "
	+ "herbs.  Your keen nose picks up the smells of an indoor pool, "
	+ "fragrant oils, and specialty soaps from the hall to the south.");
	add_smell("goblin", "The stink of mixed up herbs, harsh cleaning "
	+ "fluids, and dangerous soaps flood the cool air here.");
	add_smell("dwarf", "The air here is cool and clean.  From the east there "
	+ "is a very sterile odour of recent cleaning while to the west you pick "
	+ "up the smells of invigorating herbal blends.  From the hall to the "
	+ "south, you think you smell an indoor pool, fragrant oils, and "
	+ "specialty soaps.");
	add_smell("hobbit", "Strong herbal blends from the west make your head "
	+ "spin as you experience the cool, fragrant air here.  From the east "
	+ "there must be some serious cleaning going on judging by the sterile "
	+ "cleaning smells while from the south you think you pick up the "
	+ "smells of an indoor pool, fragrant oils, and specialty soaps.");
	add_smell("gnome", "The air here is cool and clean.  You detect "
	+ "quality, sterile cleaning fluids to the east and herb stimulants "
	+ "to the west.  To the south you believe you detect moisture "
	+ "indicative of an indoor body of water, fragrant oils commonly used "
	+ "by humans in massaging, and a variety of specialty soaps.");
	add_smell("minotaur", "Soapy, fragrant oils and odours designed to mask "
	+ "the scent of humans flood the cool, clean air here.  Harsh cleaning "
	+ "smells come from the east while to the south you detect moisture from "
	+ "an indoor pool.");
	add_smell("halfhuman", "The air here is cool and clean.  From the east "
	+ "there is a very sterile odour of recent cleaning while to the west "
	+ "you pick up the smells of invigorating herbal blends.  From the hall "
	+ "to the south, you think you smell an indoor pool, fragrant oils, and "
	+ "specialty soaps.");
	add_smell("halfelf", "The air here is cool and clean.  From the east "
	+ "there is a very sterile odour of recent cleaning while to the west "
	+ "you pick up the smells of invigorating herbal blends.  From the hall "
	+ "to the south, you think you smell an indoor pool, fragrant oils, and "
	+ "specialty soaps.");
	add_smell("orc", "The scent of manflesh tainted with herbal blends, "
	+ "harsh cleaning smells, and dangerous soaps flood your nostrils.");
	add_smell("hobgoblin", "The air here is clean and cool.  Common "
	+ "human sterilizing fluids come from the east while to the west are "
	+ "the smells of stimulating herbal blends.  From the south you believe "
	+ "you smell an indoor pool and fragrant soaps.");
	add_smell("kender", "Ahh!  The scents of exciting herbal blends waft "
	+ "in pleasantly from the west while pungent sterile cleaning smells "
	+ "come from the west.  An odd mix that!  From the hall to the south "
	+ "you smell an indoor pool, fragrant oils, and tantalizing soaps.  "
	+ "Human spas must be invigorating to investigate!");
	add_smell("drow", "The air here is refreshingly cool though a tad "
	+ "sterile due to the odours of cleaning fluids from the east.  From "
	+ "the west waft the smells of stimulants and herbal blends while to "
	+ "the south your keen nose detects the moisture from an indoor pool, "
	+ "fragrant oils, and human specialty soaps.");
	add_smell("noldor", "The air here is cool, clean, and fragrant.  The "
	+ "sterile odours of strong cleaning fluids come from the east while "
	+ "to the west come the smells of a blend of stimulating, fresh "
	+ "herbs, quite unexpected from this human establishment.  Your keen "
	+ "nose picks up the smells of an indoor pool, fragrant oils, and "
	+ "human specialty soaps from the hall to the south.");

	EXIT(NOBLE + "nplaza", "north", 0, 0);
	EXIT(NOBLE + "spa_pierce", "east", 0, 0);
	EXIT(NOBLE + "spa2", "south", 0, 0);
	EXIT(NOBLE + "spa_pamper", "west", 0, 0);
	
	CMD(({"plaza", "the plaza", "court", "the court"}), "view",
		  "@@view_plaza");
	CMD(({"pattern", "mosaic", "pinwheel", "at pattern", "at mosaic",
		"at pinwheel"}), "gaze", "@@gaze_mosaic");
	CMD("sign", "read", "@@read_sign");
	CMD("sign", "mread", "@@mread_sign");

	reset_palan_room();
}

view_plaza()
{
	/* This function returns an equivalent of 'look' from nplaza
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWNORTH->long());
	target = find_object(VIEWNORTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Through the windows along the north wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the windows along the north wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign behind the counter.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/spasign.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = NOBLE + "obj/spasign.txt";

	say(QCTNAME(TP) + " studies the marble sign behind the counter.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

int
gaze_mosaic()
{
	write("As you gaze at the enameled black pinwheel mosaic on the "
	+ "floor, you begin to experience a feeling of timelessness.  It's "
	+ "impossible to estimate what amount of time passes before you wake "
	+ "from your reverie feeling relaxed and composed.\n");
	say(QCTNAME(TP) + " stares entranced at the enameled black pinwheel "
	+ "mosaic on the floor, then blinks " + HIMSELF(TP) + " out of " + HIS(TP)
	+ " reverie.\n");
	return 1;
}
