/* 
 * The general equipment shop off Jems Court in the Aesthetics 
 * quarter of Palanthas.  Light, rope, etc.
 *

lanterns, hooded, bullseye (can be shone on something to return exa?)
big lamp
generic flasks of oil
Phosphent torch, bursts into brilliant white light (fungus regrows if not burnt out?)
	If doused with wine, will explode for dmg.  Maybe a quest guard who blocks
	but will accept tons of torches and even light them (boom!).
rope, hemp, silk
grapples
chalk
waterskins (fillable in rooms w/water)


 * Mortis 04.2006
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

inherit MONKS_ROOMBASE;
inherit "/lib/trade";

#define VIEWNORTH				(MONKS + "a12")
#define NUM	sizeof(MONEY_TYPES)

object manny;


string
query_to_jail()
{
	return "north";
}

mapping name_gear_to_info = (["torch":"With a short handle of pale, hollow "
	+ "clay the torch's tip has been wrapped in thin leather bands upon which "
	+ "grows a fuzzy, white fungus.",
	"chalk":"Held in a small, flat wooden ring at its base is a large piece "
	+ "of chalk with which you may <write> messages.",
	"lamp":"With a body like a vase this three foot high lamp is "
	+ "made from low-grade, hammered steel and holds a great reservoir "
	+ "of oil.  A large, thick wick rises from the latched lid and "
	+ "is surrounded by a cylindrical, white paper shade.  There are "
	+ "handles on either side of the body for lifting.",
	"hooded-lantern":"Five panes of glass spaced by low-grade steel are set "
	+ "into a flat base containing a concealed oil reservoir and wick.  "
	+ "Topped with a thin, angled roof, the lantern has a handle "
	+ "attached for easy carrying.",
	"bullseye-lantern":"Four thick panes of glass spaced by low-grade steel are "
	+ "set into a flat base containing a concealed oil reservoir and "
	+ "wick.  With reflective shutters on all sides but one, it is "
	+ "possible to <shine light on> things around you to examine them "
	+ "more closely.  Topped with a thin, angled roof, the lantern has a "
	+ "handle attached for easy carrying."]);

void
reset_palan_room()
{
	if (!manny)
	{
		manny = clone_object(MONKS + "living/manny");
		manny->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("A small, general equipment shop");
    LONG("The walls of this well-lit shop are built from tan bricks with "
	+ "old, gray mortar.  The aging wood of the low ceiling above sags "
	+ "noticeably.  Large lamps the size of vases burn in the corners "
	+ "atop short stools, and the walls and tables are covered with neatly "
	+ "arranged coils of rope, racks of torches, rows of lanterns, and "
	+ "other sundry gear.  An old staircase in the south climbs to the "
	+ "second floor, and beside a window in the north wall is a dark, old, "
	+ "wooden door leading out onto the street.\n");

	ITEM(({"street", "outside", "court"}), "Through the window, you could "
	+ "take a look at the cul-de-sac of Emptoris.\n");
	ITEM(({"window", "windows"}), "An open window is set into the north wall "
	+ "of the shop affording a good view of Jems Court.  You may "
	+ "<view court> to have a look.\n");
	ITEM("ceiling", "The shop is two stories with an old, drooping, wooden "
	+ "ceiling.  Stairs lead up into the south wall.\n");
	ITEM(({"stairs", "staircase"}), "A small flight of stairs "
	+ "rises to the second floor in the south of the shop.\n");
	ITEM(({"lamps", "lamp"}), "Large clay lamps the size of vases sit atop "
	+ "short stools in the corners of the shop shedding bright, even light "
	+ "about the room.\n");
	ITEM("floor", "The floor of the shop is comprised of large, "
	+ "translucent marble blocks with a tinge of beige from years of traffic "
	+ "despite daily sweeping.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls of the shop are comprised of tan bricks with "
	+ "old, gray mortar.\n");
	ITEM(({"south wall", "east wall", "west wall"}), "Arranged on racks upon "
	+ "the wall are coils of rope, racks of torches, rows of lanterns, and "
	+ "other sundry gear.  You may <peruse gear> if you like or <check> "
	+ "individual varieties for a closer look.\n");
	ITEM("north wall", "The exit door and a window are set into the "
	+ "north wall.  Through them you may enter or view Jems Court "
	+ "outside.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Large blocks of marble were "
	+ "used in the construction of the shop's floor.  They are translucent "
	+ "white like most marble in the city but tinged beige from years of "
	+ "traffic.\n");
	ITEM(({"rack", "racks", "table", "tables"}), "Wooden racks on the walls "
	+ "and tables neatly arranged in the shop hold coils of rope, rows of "
	+ "torches and lanterns, and other sundry gear.  You may <peruse gear> "
	+ "or <check> on a particular type for a closer look.\n");
	ITEM(({"coil", "coils", "rope", "ropes", "torch", "torches", "lantern",
		"lanterns"}), "Neatly arranged upon racks and tables about the "
	+ "shop are coils of rope, racks of torches, rows of lanterns, and other "
	+ "sundry gear.  You may peruse them with <peruse gear> if you wish or "
	+ "use <check> to have a closer look.\n");
	ITEM(({"sign", "wooden sign"}), "A wooden sign hangs on the south "
	+ "wall beside the stairs.  It contains instructions for ordering.  "
	+ "You may read or mread it.\n");

	add_smell("vampire", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.  The scent of blood is weak here.");
	add_smell("morgul", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.");
	add_smell("human", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell.");
	add_smell("elf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.");
	add_smell("goblin", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "goblin nostrils can't get enough of.");
	add_smell("dwarf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.");
	add_smell("hobbit", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a pungent fiery smell that makes your nose "
	+ "itch.");
	add_smell("gnome", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the distinct, pungent smell of a flammable "
	+ "fungus called Phosphentus.  What are these humans doing with that?  "
	+ "It's dangerously flammable, explosive in alcohol, and grows at an "
	+ "alarming rate.");
	add_smell("minotaur", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell.");
	add_smell("halfhuman", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell.");
	add_smell("halfelf", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell.");
	add_smell("orc", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "orcish nostrils can't get enough of.");
	add_smell("hobgoblin", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.");
	add_smell("kender", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a pungent fiery smell that makes your nose "
	+ "itch.");
	add_smell("drow", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the distinct, pungent smell of a flammable "
	+ "fungus called Phosphentus.  How did these humans acquire this deep "
	+ "cave grown growth?  It's dangerously flammable, explosive in alcohol, "
	+ "and grows like the plague.");
	add_smell("noldor", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and the uniquely pungent smell of a flammable "
	+ "fungus.");
	add_smell("uruk", "The air is filled with the smells of warm lantern "
	+ "oil, fresh hemp rope, and a uniquely pungent fiery smell that your "
	+ "uruk nostrils can't get enough of.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air thick with the rich smells of new equipment.");
	add_smell("unknown", "You smell the air rich with the smells of new "
	+ "equipment, but what the heck race are you?  Why not mail "
	+ "Krynn for fun?");

	CMD(({"gear", "equipment"}), ({"peruse"}), "@@peruse_gear");
	CMD(({"street", "north", "outside", "court"}), "view", "@@view_court");
	CMD(({"sign", "wooden sign"}), "read", "@@read_sign");
	CMD(({"sign", "wooden sign"}), "mread", "@@mread_sign");

    setuid();
    seteuid(getuid());
	clone_object(MONKS + "doors/generaleq_door_in")->move(TO);

	reset_palan_room();
}

peruse_gear() 
{
	write("You carefully peruse the lanterns, coils of rope, sticks of chalk, "
	+ "flasks of oil, lamps, and other sundry gear on the racks and tables.  "
	+ "Their quality looks good.  You can take a closer look at any of them "
	+ "with <check>.\n");
	say(QCTNAME(TP) + " carefully peruses the new, sundry gear on the racks "
	+ "and tables.\n");
	return "";
}

view_court()
{
	/* This function returns an equivalent of 'look' from a11
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
	write("Out the window along the north wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the north wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the wooden sign on the south wall.\n");
	write("The sign reads...\n");
	write(" ________________________________________\n"
	+ "|\\.______________________________________\\.\n"
	+ "| |                                       |\n"
	+ "| | o                                   o |\n"
	+ "| |    Manny's General Equipment Store    |\n"
	+ "| |                                       |\n"
	+ "| |                                       |\n"
	+ "| |  Equipment for Sale:          Price   |\n"
	+ "| |  -------------------          -----   |\n"
	+ "| |   Great Lamp                   12gc   |\n"
	+ "| |   Hooded Lantern                3gc   |\n"
	+ "| |   Bullseye Lantern              4gc   |\n"
	+ "| |   Flask of Oil                  2gc   |\n"
	+ "| |   White Torch                   2gc   |\n"
	+ "| |                                       |\n"
	+ "| |   20m of Hemp Rope              2gc   |\n"
	+ "| |   20m of Silk Rope              8gc   |\n"
	+ "| |   Grapple                       2gc   |\n"
	+ "| |                                       |\n"
	+ "| |   Leather Guige                 5gc   |\n"
	+ "| |                                       |\n"
	+ "| |   Piece of Chalk               10sc   |\n"
	+ "| |   Waterskin                     1gc   |\n"
	+ "| |                                       |\n"
	+ "| | o                                   o |\n"
	+ " \\|_______________________________________|\n"
	+ "\n");


	return 1;
}

public int
mread_sign()
{
	string file = MONKS + "obj/generaleq_sign.txt";

	say(QCTNAME(TP) + " studies the wooden sign on the south wall.\n");
	write("The sign reads...\n");
	TP->more(" ________________________________________\n"
	+ "|\\.______________________________________\\.\n"
	+ "| |                                       |\n"
	+ "| | o                                   o |\n"
	+ "| |    Manny's General Equipment Store    |\n"
	+ "| |                                       |\n"
	+ "| |                                       |\n"
	+ "| |  Equipment for Sale:          Price   |\n"
	+ "| |  -------------------          -----   |\n"
	+ "| |   Great Lamp                   12gc   |\n"
	+ "| |   Hooded Lantern                3gc   |\n"
	+ "| |   Bullseye Lantern              4gc   |\n"
	+ "| |   Flask of Oil                  2gc   |\n"
	+ "| |   White Torch                   2gc   |\n"
	+ "| |                                       |\n"
	+ "| |   20m of Hemp Rope              2gc   |\n"
	+ "| |   20m of Silk Rope              8gc   |\n"
	+ "| |   Grapple                       2gc   |\n"
	+ "| |                                       |\n"
	+ "| |   Leather Guige                 5gc   |\n"
	+ "| |                                       |\n"
	+ "| |   Piece of Chalk               10sc   |\n"
	+ "| |   Waterskin                     1gc   |\n"
	+ "| |                                       |\n"
	+ "| | o                                   o |\n"
	+ " \\|_______________________________________|\n"
	+ "\n");


	return 1;
}

void 
init()
{    
	::init();
	ADA("check");
}

int
check(string str)
{
	int k;
	string check = "";
	
	if (!str)
	{
		write("Check what?  Some of the sundry gear on the racks and "
		+ "tables?  You may want to peruse them first or even <read sign>.\n");
		return 1;
	}

	if (check = name_gear_to_info[str])
	{
		write("You check out the " + str + ".  " + check + "\n");
		say(QCTNAME(TP) + " checks out the " + str + ".\n");
		return 1;
	}
	write("That is not a valid piece of gear.  Peruse the gear "
	+ "first or even <read sign>.\n");

	return 1;
}
