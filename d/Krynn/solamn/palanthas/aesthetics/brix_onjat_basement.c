/* 
 * Basement of Onjat house run by Brix gang leader Kirk.
 * Gamble, drink (gut, an ale), snack.
 *
 * Mortis 07.2006
 *
 * Unfinished.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_ROOMBASE;

void
reset_palan_room()
{

}

void
create_palan_room()
{
    SHORT("Large, underground Onjat gaming hall");
	LONG("Several pillars of mixed red and tan bricks arc overhead into a "
	+ "ceiling of brick arches above this poorly lit, smoky gaming hall.  "
	+ "Torches burn in iron sconces here and there on the walls and brick "
	+ "pillars, their flickering flames adding to the leaf smoke and dim "
	+ "atmosphere.  The hall is filled with large Onjat tables, raucous "
	+ "patrons, serving wenches, and the unmistakable black-shirted Brix "
	+ "gangers who run the hall.\nA small sign hung by the door reads:  "
	+ "Permit Pending.\n");

	ITEM(({"torch", "sconce", "torches", "sconces"}), "Set into corroded "
	+ "iron sconces here and there on the walls and brick pillars burn "
	+ "short, thick wooden torches, their flickering flames adding to the "
	+ "leaf smoke and dim atmosphere of this underground gaming hall.\n");
	ITEM(({"floor", "wall", "walls", "ceiling", "brick", "bricks", "pillar",
		"pillars", "arch", "arches"}), "The "
	+ "floor is dark and covered with unknown stains in places concealing "
	+ "the brick beneath.  The red and tan brick walls rise straight up to "
	+ "shoulder height before curving in harmoniously with the brick pillars "
	+ "to create a ceiling of arches arcing over a dozen feet above.  The "
	+ "greyish mortar looks old, is dotted with grout, and is cracked in "
	+ "places.\n");
	ITEM(({"table", "tables"}), "Large, oval tables of thick oak fill the "
	+ "hall.  Their heavily nicked and stained grains still work well to "
	+ "contain the often sloppily thrown Onjat dice used upon them.\n");
	ITEM(({"patron", "patrons", "wench", "wenches", "ganger", "gangers"}),
	  "The hall is full of raucous patrons ranging from the destitute "
	+ "reeking of cheap alcohol to young aesthetics to noble youths slumming "
	+ "it, serving wenches carrying huge handfuls of beers, and tough, "
	+ "leering Brix gangers in their easy to spot black, sleeveless, hemp "
	+ "shirts.\n");

	add_smell("vampire", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.  The scent of blood running hard and fast here is maddening!");
	add_smell("morgul", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.");
	add_smell("human", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.");
	add_smell("elf", "The air is damp and heavy with torch and powerful leaf "
	+ "smoke and the smells of somewhat fresh human ale, perfumes and "
	+ "colognes, old brick, and the crisp, inky smell of the green dyed felt "
	+ "of the Onjat tables.");
	add_smell("goblin", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, flowery scents, old brick, "
	+ "and the pungent smell of the green dyed felt of the Onjat "
	+ "tables.  All it's missing is the odour of sewage and rot to make you "
	+ "feel at home.");
	add_smell("dwarf", "You're unsure whether this is a basement or a part "
	+ "of the humans' sewage system, but the air is damp and heavy with "
	+ "torch smoke and the smells of fresh ale, perfumes and colognes, old "
	+ "brick, and leaf and the noticeably crisp smell of the green dyed felt "
	+ "of the Onjat tables.");
	add_smell("hobbit", "The air is damp and heavy with torch and a leaf "
	+ "smoke that tickles your nose enticingly.  The smells of fresh ale, "
	+ "perfumes and colognes, old brick, and the noticeably crisp smell of "
	+ "the green dyed felt of the Onjat tables fill your senses.");
	add_smell("gnome", "The air is damp and heavy with the taint of torch "
	+ "and leaf smoke and the smells of fresh ale, perfumes and colognes, "
	+ "old brick, and the crisp, inky smell of the green dyed felt of the "
	+ "Onjat tables.  Your gnomish nose tells you the air quality has been "
	+ "compromised to dangerously unpleasant levels.");
	add_smell("minotaur", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.  None of these, however, mask the strong scent of man meat.");
	add_smell("halfhuman", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.");
	add_smell("halfelf", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the crisp, inky smell of the green dyed felt of the Onjat "
	+ "tables.");
	add_smell("orc", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.  None of these, however, mask the strong scent of manflesh.");
	add_smell("kender", "The air is damp and heavy with torch and a leaf "
	+ "smoke that tickles your nose curiously.  The smells of fresh ale, "
	+ "perfumes and colognes, old brick, and the noticeably crisp smell of "
	+ "the green dyed felt of the Onjat tables fill your senses.  It's way "
	+ "too exciting for there not to be food as well.  Of this you are "
	+ "sure.");
	add_smell("drow", "You're unsure whether this is a basement or a part "
	+ "of the surface dwellers' sewage system, but the air is damp and heavy "
	+ "with torch smoke and the smells of fresh ale, perfumes and colognes, "
	+ "old brick, and leaf and the noticeably crisp smell of the green dyed "
	+ "felt of the Onjat tables.");
	add_smell("noldor", "The air is damp and heavy with torch and powerful "
	+ "leaf smoke and the smells of somewhat fresh human ale, perfumes and "
	+ "colognes, old brick, and the crisp, inky smell of the green dyed felt "
	+ "of the Onjat tables.  How distasteful.  These humans live like "
	+ "dwarves.");
	add_smell("uruk", "The air is damp and heavy with torch and leaf "
	+ "smoke and the smells of fresh ale, perfumes and colognes, old brick, "
	+ "and the noticeably crisp smell of the green dyed felt of the Onjat "
	+ "tables.  None of these, however, mask the strong scent of manflesh.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the smells of a gaming hall.");
	add_smell("unknown", "You smell the air rich with the smells of a human "
	+ "gaming hall, but what the heck race are you?  Why not mail Krynn for "
	+ "fun?");

/*	set_tell_time(90);
	add_tell("@@get_tells@@" + "\n");

	CMD(({"door", "arch", "archway", "doorway"}), "enter", "@@enter_door");
*/
	EXIT(MONKS + "alley051", "east", 0, 0);

	reset_palan_room();
}

/*string
guards_on_door()
{
	if (!guard1 && !guard2)
		return "There is no one around so you may <enter door> if you wish "
		+ "to attempt an entrance.";
	
	if (guard1 && guard2)
		return "There is a pair of guards beside it keeping an eye on those "
		+ "attempting to pass.  If you're bold enough, you may <enter door> "
		+ "to see if they'll let you through.";

	return "There is a guard beside it keeping an eye on those "
	+ "attempting to pass.  If you're bold enough, you may <enter door> "
	+ "to see if he'll let you through.";
}

int
enter_door()
{
	string guard_desc;
	object guardx;

	if (guard1 || guard2)
	{
		if (guard1)
			guardx = guard1;
		else
			guardx = guard2;

		guard_desc = guardx->short();

		if (TP->query_prop(LIVE_I_ATTACKED_BRIX) == 1)
		{
			guardx->command("laugh evil");
			guardx->command("asay angr Enter over my dead body, foe!");
			write("The " + guard_desc + " bars you from entering the door.\n");
			say(QCTNAME(TP) + " tries to pass through the door to the west, "
			+ "but is barred by the " + guard_desc + ".\n");
			return 1;
		}

		if (TP->query_align() >= 100)
		{
			write("The " + guard_desc + " looks you over warily.\n");
			say("The " + guard_desc + " looks " + QTNAME(TP) + " over "
			+ "warily.\n");
			guardx->command("asay menac I let you in, but cause trouble and "
			+ "you leave sack by sack.  Jum jee?");
		}

		else
			guardx->command("emote nods his head curtly.");
	}

	write("You step through the doorway.\n");
	TP->move_living("stepping through the doorway to the west",
		MONKS + "brix_onjat_basement", 1, 0);
	return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
*/