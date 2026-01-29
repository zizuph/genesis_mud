/* 
 * Kirk's second floor hq off Jems Court.
 *
 * Mortis 06.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define VIEWWEST			(MONKS + "alley055")

inherit MONKS_ROOMBASE;

object hood1, hood2;

void
reset_palan_room()
{
	if (!hood1)
	{
		hood1 = clone_object(MONKS + "living/brix_ganger_doc");
		hood1->move(TO);
	}

	if (!hood2)
	{
		hood2 = clone_object(MONKS + "living/brix_ganger_kirk");
		hood2->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("On the second floor of a dilapidated, crumbling gang house");
    LONG("With walls of dirty, moldy, tan brick and a floor and ceiling "
	+ "of warped and aged, grey wood this one time master room is now a "
	+ "hovel for the gangs of Jems court.  The windows are boarded up except "
	+ "for one in the west, and the cots, desk, and stools are old and in "
	+ "disrepair.  A twisted, dilapidated staircase spirals down in the "
	+ "east to the parlour.\n");

	ITEM("house", "Any house in particular?  You're in a house.  Why not "
	+ "have a <look> around?\n");
	ITEM(({"floor"}), "The aged, grey wooden boards of the floor "
	+ "are warped and creak when walked upon.\n");
	ITEM(({"ceiling"}), "The aged, grey wooden boards of the vaulted ceiling "
	+ "that supports the roof sag dangerously close to snapping and "
	+ "collapsing, perhaps bringing the entire house down with them.  You "
	+ "spot a rope handled trapdoor sawed into the northeast corner of the "
	+ "roof.\n");
	ITEM("trapdoor", "Sawed directly through the ceiling in the northeast "
	+ "corner of the roof with a knotted length of rope stuck through an "
	+ "eye for a handle is a trapdoor.  You notice the wooden planks "
	+ "surrounding it look too old and dilapidated to support much weight.\n");
	ITEM(({"cot", "cots", "desk", "stool", "stools"}), "Furniture that looks "
	+ "as if it was built in the old age, the cots, desk, and stools look "
	+ "just sturdy enough to use without fear of injury.\n");
	ITEM(({"wall", "walls"}), "Built of old, tan bricks spotted with mold "
	+ "and covered with dirt, the walls are in extreme disrepair.  The "
	+ "north wall is bowed outward, and much of the mortar in the south is "
	+ "cracked and crumbling.\n");
	ITEM(({"window", "windows", "west window"}), "The windows in the north "
	+ "and south are boarded up, but the one in the west still has a few "
	+ "broken panes of glass.  You may look out it and <view> the court "
	+ "down below.\n");

	add_smell("vampire", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  The scent of blood is stronger "
	+ "here.");
	add_smell("morgul", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("human", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("elf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The ghastly combination turns your stomach.");
	add_smell("goblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("dwarf", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.");
	add_smell("hobbit", "The air is tainted with the smells of stale alcohol "
	+ "and urine, but the leaf smoke in the air makes your nose twitch "
	+ "curiously.");
	add_smell("gnome", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  By human standards this must be acceptable, "
	+ "but your gnomish nose tells you the air quality has been compromised "
	+ "to dangerous levels.");
	add_smell("minotaur", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfhuman", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.");
	add_smell("halfelf", "The air is tainted with the smells of stale "
	+ "alcohol, leaf smoke, and urine.  It is rather unpleasant.");
	add_smell("orc", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  It reminds you of home.");
	add_smell("hobgoblin", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("kender", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  Gross!");
	add_smell("drow", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  These surface dwellers live like pigs.");
	add_smell("noldor", "The air is tainted with the smells of stale alcohol, "
	+ "leaf smoke, and urine.  The revolting combination sickens you.");
	add_smell("uruk", "The air is filled with the smells of old booze, "
	+ "smoke, and piss.  Filthy but welcoming in a homely sort of way.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the smells of a human back alley.");
	add_smell("unknown", "You smell the air rich with the smells of a human "
	+ "back alley, but what the heck race are you?  Why not mail Krynn for "
	+ "fun?");

	CMD(({"west", "w", "court", "window"}), "view", "@@view_west");
	CMD(({"trapdoor", "trap door"}), ({"enter", "climb"}), "@@use_trapdoor");

	EXIT(MONKS + "brix_kirk_parlour", "down", 0, 0);
	
	reset_palan_room();
}

int
view_west()
{
	/* This function returns an equivalent of 'look' from alley055
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWWEST->long());
	target = find_object(VIEWWEST);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From above you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Down below you see ",
						"You notice below ",
						"Down below you spy "}))
						+ desc + " outside the house.\n");
 
	return 1;
}

int
use_trapdoor()
{
	if (random(3) == 1)
	{
		write("You attempt to climb up to reach the trapdoor, but one of "
		+ "the ceiling planks SNAPS sending you falling back down in a heap "
		+ "of thick, grey dust!\n");
		say(QCTNAME(TP) + " attempts to climb up to reach a trapdoor in "
		+ "the northeast of the ceiling, but one of the ceiling planks SNAPS "
		+ "sending " + HIM(TP) + " falling back down in a heap of thick, "
		+ "grey dust!\n");
		return 1;
	}

	if (TP->query_skill(SS_CLIMB) >= 27 + random(11))
	{
		write("You climb up to the trapdoor, push it open with a wood-"
		+ "straining CREEEEAK, and climb out onto the heavily sagging "
		+ "roof.\n");
		say(QCTNAME(TP) + " climbs up to a trapdoor in the northeast of "
		+ "the ceiling, pushes it open with a wood-straining CREEEEAK, "
		+ "and disappears as " + HE(TP) + " climbs out.\n");
		TP->move_living("climbing out the trapdoor",
			MONKS + "brix_kirk_roof", 1, 0);
		return 1;
	}

	write("You scramble up the wall trying to reach the trapdoor but can't "
	+ "seem to reach it.  Perhaps you need a climbing aid?\n");
	say(QCTNAME(TP) + " scrambles up the wall trying to reach something in "
	+ "the northeast of the ceiling but slides back down unsuccessfully.\n");
	return 1;
}
