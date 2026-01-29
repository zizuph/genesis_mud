/* 
 * The bowyer on the outskirts of the Arms district
 * of the merchants quarter of Palanthas.
 *
 * Mortis 03.2006
 *
 * Add function to allow use of archery targets for practice.
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>
#include <files.h>
#include <formulas.h>

inherit MERCH_ROOMBASE;
inherit "/lib/trade";

#define VIEWEAST				(MERCH + "m16")
#define NUM	sizeof(MONEY_TYPES)

object aug;

string
query_to_jail()
{
	return "east";
}

void
reset_palan_room()
{
	if (!aug)
	{
		aug = clone_object(MERCH + "living/aug");
		aug->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("Bowyer on outskirts of Arms district");
    LONG("Inside, this marble building has a high, arched roof and stretches "
	+ "a good hundred paces to the west where straw archery targets are "
	+ "arranged.  A redwood counter is to the north by the door and behind "
	+ "it hung on racks on the walls are a variety of bows.  Above them is a "
	+ "wooden sign.  A window opens out onto Palanthas Circle in the east "
	+ "beside the door.\n");

	ITEM(({"outside", "street", "palanthas circle"}), "Through the window, you "
	+ "could take a look at Palanthas Circle with <view street>.\n");
	ITEM(({"window", "windows"}), "An open window is set into the east wall "
	+ "of the shop affording a good view of Palanthas Circle outside and "
	+ "stirring the air with a cool breeze.  You may <view street> to have a "
	+ "look.\n");
	ITEM("ceiling", "The building is one story with a ceiling of arched "
	+ "wooden beams high enough to fire arrows a short distance beneath.\n");
	ITEM("floor", "The floor of the bowyer's is comprised of large, "
	+ "translucent marble blocks.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls are built of translucent marble blocks.  Though "
	+ "clean, they are dull and most be some of the oldest in this section "
	+ "of the city.\n");
	ITEM("north wall", "Upon the north wall behind a redwood counter are "
	+ "hung a great variety of bows for sale.  Above them hangs a wooden "
	+ "sign.\n");
	ITEM("south wall", "There is a table along the south wall with tools "
	+ "used in fletching and the shaping and finishing of bows.\n");
	ITEM("east wall", "The exit door and a window are set into the "
	+ "east wall.  Through them you may enter or view the street of "
	+ "Palanthas Circle outside.\n");
	ITEM("west wall", "Several straw archer targets rest against the west "
	+ "wall or hung upon it for customers to try out their bows.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Particularly large "
	+ "blocks of marble were used in the construction of the building.  They "
	+ "are translucent white like most marble in the city but are dull from "
	+ "age.\n");
	ITEM(({"tool", "tools"}), "On a table by the south wall are arranged "
	+ "wood working and fletching tools used by the bowyer to craft "
	+ "arrows and work on bows.\n");
	ITEM(({"rack", "racks"}), "Redwood racks hold a variety of bows on "
	+ "the north wall.\n");
	ITEM(({"table"}), "A redwood table along the south wall bears an "
	+ "arrangement of tools used in fletching in bow crafting.\n");
	ITEM(({"bow", "bows"}), "A vast assortment of bows hangs on racks on "
	+ "the north wall.  <read sign> for information on purchasing a custom "
	+ "one or <peruse bows> to have a closer look.\n");
	ITEM(({"sign", "wooden sign"}), "A wooden sign hangs on the north wall "
	+ "above an assortment bows providing information on ordering a custom "
	+ "bow.\n");
	ITEM("door", "An open door leads east onto the street of Palanthas "
	+ "Circle near the Arms district.\n");
	ITEM(({"lamp", "lamps"}), "Small oil lamps rest in various places about "
	+ "the place providing light at night.\n");
	ITEM(({"target", "targets"}), "Straw archery targets "
	+ "are arranged along and hung upon the west wall for customers to test "
	+ "their new bows and arrows.  Built of straw, they are tied tightly "
	+ "into packed concentric circles to easily catch arrows provided they "
	+ "are on target.\n");

	add_smell("vampire", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  The scent of blood is weak here.");
	add_smell("morgul", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("human", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("elf", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  You detect the faintest hint of "
	+ "some vaguely familiar bestial scent.");
	add_smell("goblin", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window mixed with the faintest hint of "
	+ "hobgoblin.");
	add_smell("dwarf", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("hobbit", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  Nothing pleasant to eat or drink reaches "
	+ "your nose here.");
	add_smell("gnome", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("minotaur", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("halfhuman", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("halfelf", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.");
	add_smell("orc", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  You detect the faintest hint of "
	+ "some vaguely familiar bestial scent.");
	add_smell("hobgoblin", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("kender", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  Nothing pleasant to eat or drink reaches "
	+ "your nose here.");
	add_smell("drow", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  You detect the faintest hint of "
	+ "some vaguely familiar bestial scent.");
	add_smell("noldor", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  You detect the faintest hint of "
	+ "some vaguely familiar bestial scent like goblin.");
	add_smell("uruk", "The hint of fresh redwood and straw waft about on a "
	+ "breeze from the east window.  You detect the faintest hint of "
	+ "some vaguely familiar bestial scent.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "hot sooty air or armament oils or polishing solutions.");
	add_smell("unknown", "You smell the fresh redwood and straw in the air, "
	+ "but what the heck race are you?  Why not mail Krynn for fun?");

	EXIT(MERCH + "m16", "east", 0, 0);
	
	CMD(({"bow", "bows"}), ({"peruse"}), "@@peruse_wep");
	CMD(({"circle", "outside", "street", "the street", "palanthas circle"}),
		"view", "@@view_plaza");
	CMD(({"sign", "marble sign"}), "read", "@@read_sign");
	CMD(({"sign", "marble sign"}), "mread", "@@mread_sign");

	reset_palan_room();
}

string
peruse_wep() 
{
	write("You carefully peruse the bows on the wall.  There is a "
	+ "wide variety of medium sized bows, shortbows, and longbows of "
	+ "several kinds of woods finished in almost any variety you can "
	+ "imagine.  Why not <read sign> for an organized list of choices?\n");
	say(QCTNAME(TP) + " carefully peruses the racks of weapons on the west "
	+ "wall.\n");
	return "";
}

int
view_plaza()
{
	/* This function returns an equivalent of 'look' from m16
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWEAST->long());
	target = find_object(VIEWEAST);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Out the window along the east wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the street you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the east wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the wooden sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/bowyer_sign.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
	string file = MERCH + "obj/bowyer_sign.txt";

	say(QCTNAME(TP) + " studies the wooden sign on the west wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

void 
init()
{    
	::init();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

}
