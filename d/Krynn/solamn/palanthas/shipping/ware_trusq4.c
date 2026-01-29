/*
 * Mortis 03.2005 
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
  return "north";
}

object worker1, worker2, worker3;

void
reset_palan_room()
{
	if (!worker1)
	{
		worker1 = clone_object(SHIP + "living/trusq_worker");
		worker1->move(TO);
	}

	if (!worker2)
	{
		worker2 = clone_object(SHIP + "living/trusq_worker");
		worker2->move(TO);
	}

	if (!worker3)
	{
		worker3 = clone_object(SHIP + "living/trusq_worker");
		worker3->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("Inside a large warehouse");
    LONG("This vast warehouse is filled with row upon row of crates, boxes, "
	+ "chests, bags, and the dock workers who handle them.  The floor is "
	+ "covered in sawdust, and the warehouse stretches further east.\n");

	ITEM(({"wall", "walls"}), "The bottom three feet of the walls in this "
	+ "warehouse are built with blocks of translucent white marble.  From "
	+ "there up, sturdy wooden beams and planks take over rising to the top "
	+ "of the two score foot ceiling.\n");
	ITEM("floor", "The floor is made of large blocks of translucent white "
	+ "marble and has been covered in sawdust for traction even when wet.\n");
	ITEM("sawdust", "Sawdust covers the floor for safety and traction even "
	+ "when wet.\n");
	ITEM("ceiling", "The ceiling has been built from great wooden rafters "
	+ "and rises two score feet at its pinnacle allowing inventories to be "
	+ "stacked to great heights.\n");
	ITEM(({"crate", "crates", "box", "boxes", "chest", "chests", "bag",
	  "bags"}), "A wide variety of goods in crates, boxes, chests, and bags "
	+ "are stacked high in rows filling the warehouse.\n");

	add_smell("vampire", "The air is rich with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.  You are not far from "
	+ "blood.");
	add_smell("morgul", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("human", "The air is rich with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("elf", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, sawdust, and other materials common on the piers of "
	+ "human cities.");
	add_smell("goblin", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("dwarf", "The air is rich with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("hobbit", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, sawdust, and other materials common on the piers of "
	+ "human cities.");
	add_smell("gnome", "The salty air from the bay brings with it the smells "
	+ "of common ship maintenance components such as tar, wood, and sawdust "
	+ "as well as common trade goods and spices typical in a human port.");
	add_smell("minotaur", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("halfhuman", "The air is rich with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("halfelf", "A salty breeze off the bay brings with it the "
	+ "smells of wood, tar, sawdust, and other materials common on the piers "
	+ "of human cities.");
	add_smell("orc", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.  The scent of manflesh "
	+ "is strong here.");
	add_smell("hobgoblin", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.");
	add_smell("kender", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, sawdust, and other materials common on the piers of "
	+ "human cities.");
	add_smell("drow", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, sawdust, and other materials common on the piers of "
	+ "human cities.");
	add_smell("noldor", "A salty breeze off the bay brings with it the smells "
	+ "of wood, tar, sawdust, and other materials common on the piers of "
	+ "human cities.");
	add_smell("uruk", "The air is thick with the smells of wood, tar, and "
	+ "sawdust borne on a salty breeze from the bay.  The scent of manflesh "
	+ "is strong here.");
	add_smell("presence", "The air smells like it is near the bay, but you "
	+ "fail to appreciate it fully in your current form.");
	add_smell("unknown", "The salty air is rich with wood, tar, and the like, "
	+ "but what the heck race are you?  Why not mail Krynn for fun?");

	EXIT(SHIP + "ware_trusq", "east", 0, 0);

	reset_palan_room();
}
