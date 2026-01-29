/*
 * Queen's drawing room
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
 
void reset_room();
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("Queen's drawing room");
    set_long("   This private room is very formal looking. This " +
		"where the Queen takes care of business relating to " +
		"her court. Like the rest of the castle, mother of " +
		"pearl covers the walls. Floral designs decorate the " +
		"walls and are inlaid with numerous jewels. The ceiling " +
		"has a large fresco on it. Some chairs, and a " +
		"large table dominate the room. A deep luxurious " +
		"carpet, bearing the royal insignia of the Queen, " +
		"fills the room. A chandelier hangs from the ceiling, " +
		"illuminating the room.\n\n");
	
    add_item(({"wall", "walls"}),
        "The walls polished to a dazzling whiteness. The light " +
		"from the chandelier causes the jewels to sparkle. " +
		"Flowing arabesques are carved into the panels. " +
		"Arranged around the walls are flower arrangements.n");

    add_item(({"floor", "ground", "down", "rug", "carpet"}),
        "The carpet is a rich deep blue. The Queen's ensignia " +
		"has been woven into the carpet. It is of a lioness " +
		"bearing a red rose.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall.\n");
    add_item(({"arabesque", "arabesques"}),
        "They are ornamental designs of intertwining flowers, " +
        "leaves, and geometric shapes.\n");
	add_item("furniture",
		"You see some chairs and a table in the room.\n");
	add_item("table",
		"The table is large. It is carved out of oak and is used " +
		"for conferences. Several chairs sit around it.\n");
	add_item("chairs",
		"There are some tall backed chairs. They are expertly " +
		"carved and comfortable looking. One grand chair, " +
		"designated for the Queen, sits at the head of the " +
		"table.\n");
    add_item("fresco",
		"The painting depicts the benevolence of the Queen.\n");
    add_item("chandelier", 
        "The chandelier is enormous. It's multi-tiered and covered " +
        "with diamonds. Candles burn brightly, filling the " +
        "room with light. The diamonds move slightly, catching the " +
        "candlelight and throwing it onto the walls in a " +
        "rainbow of patterns.\n");
	add_item("jewels",
		"You see emeralds, diamonds, rubies, sapphires, plus " +
		"many other gemstones set into the designs. The worth of " +
		"all the gemstones is staggering.\n");

    add_exit( TCASTLE_DIR + "q_ac",      "east");
    add_exit( TCASTLE_DIR + "q_chamber", "west");
}


void
reset_room()
{
}
