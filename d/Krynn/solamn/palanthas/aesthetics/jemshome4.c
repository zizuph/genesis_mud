/*
 * Home off Aesthetics row.
 *
 * Mortis 09.2006
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MONKS_ROOMBASE;

string
query_to_jail()
{
	return "south";
}

int num_kids = (5 - random(6));
object mom, dad, kid1, kid2, kid3, kid4, kid5;

void
reset_palan_room()
{
	if (!dad && random(3))
	{
		dad = clone_object(MONKS + "living/jemsdad");
		dad->move(TO);
	}
	if (!mom && random(4) != 1)
	{
		mom = clone_object(MONKS + "living/jemsmom");
		mom->move(TO);
	}
	
	if (num_kids == 0)
		return;
	
	if (num_kids > 0)
	{
		if (!kid1 && random(3) != 1)
		{
			kid1 = clone_object(MONKS + "living/jemschild");
			kid1->move(TO);
		}
	}
	if (num_kids > 1)
	{
		if (!kid2 && random(3) != 1)
		{
			kid2 = clone_object(MONKS + "living/jemschild");
			kid2->move(TO);
		}
	}
	if (num_kids > 2)
	{
		if (!kid3 && random(3) != 1)
		{
			kid3 = clone_object(MONKS + "living/jemschild");
			kid3->move(TO);
		}
	}
	if (num_kids > 3)
	{
		if (!kid3 && random(2) != 1)
		{
			kid4 = clone_object(MONKS + "living/jemschild");
			kid4->move(TO);
		}
	}
	if (num_kids > 4)
	{
		if (!kid5 && random(3) == 1)
		{
			kid5 = clone_object(MONKS + "living/jemschild");
			kid5->move(TO);
		}
	}
}

void
create_palan_room()
{
    SHORT("The ground floor of a tiny, poor house on the court");
    LONG("Mismatched red bricks dot the old, worn, beige brick floor of "
	+ "this small house.  Among its sparse furnishings are a table, chairs, "
	+ "a small fireplace, cupboards, and a half-oval rug by the fire.  "
	+ "Wooden steps, bowed from age and use, climb to the second floor "
	+ "room, and a thin, wooden door leads south onto Jems court.\n");

	ITEM(({"fire", "fireplace", "rug"}), "A worn, half-oval rug rests in "
	+ "front of the beige brick fireplace.  Though not capable of holding "
	+ "a roaring fire, it is enough for cooking and provides enough heat "
	+ "in this mild, seaside climate.\n");
	ITEM(({"brick", "bricks", "floor"}), "The beige bricks of the floor are "
	+ "uneven in places and very worn.  They must be extremely old.  Newer "
	+ "red bricks have been used to fill in holes and replace broken "
	+ "original bricks.\n");
	ITEM(({"wall", "walls"}), "The north and south walls are brick, but the "
	+ "east and west walls are brick for only a few feet before switching to "
	+ "wooden slats above that.\n");
	ITEM("ceiling", "Close fitting wooden boards form the ceiling overhead "
	+ "bowing in slightly in the middle.\n");
	ITEM(({"table", "chair", "chairs"}), "Simple, well-used chairs and a "
	+ "table sit in front of the fire.  Though old and not fancy, they serve "
	+ "well for daily use.\n");
	ITEM(({"cupboard", "cupboards", "cabinet", "cabinets"}), "Unfinished but "
	+ "sanded cupboards and cabinets line the walls near the west wall.  "
	+ "That area of the room must be designated for cooking.\n");
	ITEM(({"step", "steps", "stairs"}), "Wooden steps, bowed from age and "
	+ "use, climb to the second floor along the east wall.\n");
	ITEM("house", "You're in the house.  Why not have a <look> around?\n");

	add_smell("vampire", "Hints of salty air lay below the dusty air filled "
	+ "with the smells of wood, brick, and recent human cooking over a "
	+ "fire.  Fresh blood is closeby in this home.");
	add_smell("morgul", "Hints of salty air lay below the dusty air filled "
	+ "with the smells of wood, brick, and recent human cooking over a "
	+ "fire.");
	add_smell("human", "The air is a bit dusty but you can still almost "
	+ "smell the salty air from the bay mingling with the familiar homey "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("elf", "The air is a bit dusty but you can still smell the "
	+ "salty air from the bay mingling with the stuffy human home "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("goblin", "Mmmmmm, smells like humans live here.  You pick up "
	+ "the distinct smell of humans dwelling here along with the smells of "
	+ "wood, brick, and recent flame cooking.");
	add_smell("dwarf", "The air is a bit dusty but you can still smell the "
	+ "salty air from the bay mingling with the human home "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("hobbit", "Through the dust in the air, you can still smell a "
	+ "bit of the salty air from the bay.  It smells like a human home with "
	+ "the smells of wood, brick, and savory cooking over a fire filling "
	+ "your nostrils.");
	add_smell("gnome", "The air is a bit dusty but you can still smell the "
	+ "salty air from the bay mingling with the human home smells of wood, "
	+ "brick, and recent cooking over the fire.  Air quality is poor, but "
	+ "acceptable.");
	add_smell("minotaur", "Mmmmmm, smells like humans live here.  You pick up "
	+ "the distinct smell of human flesh here along with the smells of "
	+ "wood, brick, and recent flame cooking.");
	add_smell("halfhuman", "The air is a bit dusty but you can still almost "
	+ "smell the salty air from the bay mingling with the familiar homey "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("halfelf", "The air is a bit dusty but you can still almost "
	+ "smell the salty air from the bay mingling with the not unfamiliar "
	+ "homey smells of wood, brick, and recent cooking over the fire.");
	add_smell("orc", "Mmmmmm, smells like humans live here.  You pick up "
	+ "the distinct smell of manflesh here along with the smells of "
	+ "wood, brick, and recent flame cooking.");
	add_smell("hobgoblin", "Mmmmmm, smells like humans live here.  You pick up "
	+ "the distinct smell of humans dwelling here along with the smells of "
	+ "wood, brick, and recent flame cooking.");
	add_smell("kender", "Through the dust in the air, you can still smell a "
	+ "bit of the salty air from the bay.  It smells like a human home with "
	+ "the smells of wood, brick, and savory cooking over a fire filling "
	+ "your nostrils.  No doubt there must be tasty human treats hidden all "
	+ "over begging to be found.");
	add_smell("drow", "The air is a bit dusty but you can still smell the "
	+ "salty air from the bay mingling with the stuffy human home "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("noldor", "The air is a bit dusty but you can still smell the "
	+ "salty air from the bay mingling with the crude and stuffy human home "
	+ "smells of wood, brick, and recent cooking over the fire.");
	add_smell("uruk", "It smells like humans live here.  You pick up "
	+ "the distinct smell of manflesh here along with the smells of "
	+ "wood, brick, and recent flame cooking.");
	add_smell("presence", "You get little from the dusty air in your present "
	+ "form.");
	add_smell("unknown", "The dusty air and smells of a human home "
	+ "come to you, but what the heck race are you?  Why not "
	+ "mail Krynn for fun?");

	clone_object(MONKS + "doors/a19_door_in")->move(TO);

	reset_palan_room();
}
