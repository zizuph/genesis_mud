/* 
 * Sewer tunnel access off Jems Court.
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

object hood1, hood2;

void
reset_palan_room()
{
	if (!hood1)
	{
		hood1 = clone_object(MONKS + "living/brix_ganger_low");
		hood1->move(TO);
	}

	if (!hood2)
	{
		hood2 = clone_object(MONKS + "living/brix_ganger_low");
		hood2->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("In a red and tan brick tunnel sloping up to the east and "
	+ "Jems Court");
	LONG("Mixed red and tan bricks curve up the walls arcing overhead to "
	+ "form a tunnel sloping up to the east and leveling out west to a "
	+ "darkened wooden door.  The air is damp and moldy but moved by a "
	+ "breeze that picks up in gusts.\n");

	ITEM(({"court", "jems court", "jems", "housing district", "houses"}),
	  "A large housing district unfolds around Jems Court up the tunnel "
	+ "to the east.\n");
	ITEM("house", "You cannot get a look at any of the houses from down "
	+ "here in the tunnel.\n");
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
	ITEM("door", "Down the tunnel to the west is a door you can barely make "
	+ "out in the darkness.\n");

	add_smell("vampire", "The air is heavy with the smells of mold, dank "
	+ "wet things, and old crumbling mortar.  The scent of blood is weak "
	+ "here.");
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

	EXIT(MONKS + "alley053", "east", 0, 0);
	EXIT(MONKS + "alley051", "west", 0, 0);

	reset_palan_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
