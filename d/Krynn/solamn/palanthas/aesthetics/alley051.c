/* 
 * Guarded basement access to Onjat house.
 *
 * Mortis 05.2006
 * 
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_ROOMBASE;
inherit MONKS + "sewer_noises";

string
query_to_jail()
{
	return "east";
}

object guard1, guard2;

void
reset_palan_room()
{
	if (!guard1)
	{
		guard1 = clone_object(MONKS + "living/brix_ganger_chug");
		guard1->move(TO);
	}

	if (!guard2)
	{
		guard2 = clone_object(MONKS + "living/brix_ganger_nhizz");
		guard2->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("In a red and tan brick tunnel sloping up to the east and "
	+ "ending in a wall with a door to the west");
	LONG("Mixed red and tan bricks curve up the walls arcing overhead to "
	+ "form a tunnel sloping up to the east and ending in the west at a "
	+ "darkened wooden door recessed into a shadowed archway in the wall.  "
	+ "A torch burning in a sconce to the right of the door sheds flickering "
	+ "light off the brick walls and puddles.  The air is damp and moldy "
	+ "but moved by a breeze occasionally.\n");

	ITEM(({"debris", "litter"}), "Bottles, broken glass, broken old wooden "
	+ "shingles, and broken red and tan bricks here and there litter the "
	+ "floor of this tunnel.  The street cleaners must not come down here "
	+ "for some reason.\n");
	ITEM("tunnel", "You are in the tunnel.  Have a <look> around.\n");
	ITEM(({"floor", "wall", "walls", "ceiling", "brick", "bricks"}), "The "
	+ "floor is dark, dirty, and covered with puddles in places concealing "
	+ "the brick beneath.  The red and tan brick walls rise straight up a "
	+ "few feet before curving in to create a domed ceiling arcing above you "
	+ "over a dozen feet.  The greyish mortar looks ancient, is dotted with "
	+ "mold and grout, and is crumbling in places.\n");
	ITEM(({"torch", "sconce"}), "Set into a corroded iron sconce to the "
	+ "right of the door burns a short, thick wooden torch.\n");
	ITEM(({"arch", "archway", "door"}), "Recessed into a shadowed archway "
	+ "is a battered, nicked door of dark, dank wood reinforced with three "
	+ "iron bands.  " +  "@@guards_on_door@@" + "\n");
	ITEM(({"band", "bands", "iron band", "iron bands"}), "Three thin iron "
	+ "bands cross the worn, old door reinforcing it.\n");

	add_smell("vampire", "The air is heavy with the smells of mold, dank "
	+ "wet things, and old crumbling mortar.  The scent of blood is weak "
	+ "here, but through the door to the west, blood runs hard and fast.");
	add_smell("morgul", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar.");
	add_smell("human", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar.");
	add_smell("elf", "The air is damp and heavy with the smells of mold, "
	+ "dank water, crumbling mortar, and sewage.");
	add_smell("goblin", "The air is damp, wet, and reminiscent of caves "
	+ "you've lived in with all the familiar smells of rot and sewage.");
	add_smell("dwarf", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar leaving little doubt this is part "
	+ "of the humans' sewage system.");
	add_smell("hobbit", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar, but the leaf smoke in the air makes "
	+ "your nose twitch curiously.");
	add_smell("gnome", "The air is damp and tainted with the smells of mold, "
	+ "dank water, and crumbling mortar leaving little doubt this is part of "
	+ "the humans' sewage system.  Your gnomish nose tells you the air "
	+ "quality has been compromised to dangerous levels.");
	add_smell("minotaur", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar.");
	add_smell("halfhuman", "The air is damp and heavy with the smells of "
	+ "mold, dank water, and crumbling mortar.");
	add_smell("halfelf", "The air is damp and heavy with the smells of mold, "
	+ "dank water, crumbling mortar, and sewage.");
	add_smell("orc", "The air is damp, wet, and reminiscent of caves "
	+ "you've lived in with all the familiar smells of rot and sewage.");
	add_smell("hobgoblin", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar leaving little doubt this is part "
	+ "of the humans' sewage system.");
	add_smell("kender", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar.  Gross, but intriguing.");
	add_smell("drow", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar leaving little doubt this is part "
	+ "of the surface dwellers' sewage system.");
	add_smell("noldor", "The air is damp and heavy with the smells of mold, "
	+ "dank water, crumbling mortar, and sewage.  Quite distasteful.  These "
	+ "humans live like dwarves.");
	add_smell("uruk", "The air is damp and heavy with the smells of mold, "
	+ "dank water, and crumbling mortar leaving little doubt this is part "
	+ "of the humans' sewage system.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air filled with the smells of a tunnel.");
	add_smell("unknown", "You smell the air rich with the smells of a human "
	+ "sewer, but what the heck race are you?  Why not mail Krynn for "
	+ "fun?");

	set_tell_time(90);
	add_tell("@@get_tells@@" + "\n");

	CMD(({"door", "arch", "archway", "doorway"}), "enter", "@@enter_door");

	EXIT(MONKS + "alley052", "east", 0, 0);

	reset_palan_room();
}

string
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
