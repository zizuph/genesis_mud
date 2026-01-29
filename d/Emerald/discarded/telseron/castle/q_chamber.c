/*
 * Queen's private chamber
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
    set_short("Queen's private chamber");
    set_long("   This private room is where the Queen relaxes " +
		"and enjoys herself. The walls are paneled with cherry " +
		"wood, and give the room a relaxed feeling. Arabesque " +
		"designs have been carved into the panel, adding a " +
		"decorative touch to the wood. A deep luxurious carpet " +
		"fills the room. Various items fill the room, adding a " +
		"personalized touch. The room is comfortably furnished " +
		"with sofas, loveseats, chairs, tables and lamps.\n");

    add_item(({"wall", "walls"}),
        "The walls covered with cherry wood panels. The wood is " +
        "polished to a deep rich red. Flowing arabesques are " +
        "carved into the panels. Arranged around the walls are " +
		"flower arrangements.n");
    add_item(({"floor", "ground", "down", "rug", "rugs",
               "carpet", "carpets"}),
        "The carpet is a rich deep blue. Floral designs have " +
        "been intricately woven into it.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall.\n");
    add_item(({"arabesque", "arabesques"}),
        "They are ornamental designs of intertwining flowers, " +
        "leaves, and geometric shapes.\n");
	add_item("furniture",
		"You see a sofa, a loveseat, some tables, chairs, lamps, and " +
		"a desk arranged here.\n");
    add_item("sofa",
		"The sofa is overstuffed but quite inviting. It is " +
		"forest green and is decorated in a deep burgandy paisley " +
		"pattern.\n");

	add_item(({"loveseat", "loveseats"}),
		"Both loveseats are like the sofa. They are overstuffed, " +
		"comfortable, and decorated in the same manner.\n");
	add_item("tables",
		"You notice some end tables arranged by the sofa and " +
		"loveseats as well as some tall ones with flower " +
		"arrangements on them. They are made from oak, " +
		"expertly carved, and polished to a deep shine.\n");
	add_item("chairs",
		"There are some tall backed chairs situated by the " +
		"doors. They are expertly carved and comfortable looking.\n");
	add_item(({"lamp", "lamps"}),
		"Stately crystal lamps are spread around the room. " +
		"They fill the chamber with a soft, warm glowing light.\n");
	add_item("desk",
		"An ornately carved desk sits in the room. This seems " +
		"to be where the Queen does her letter writing and " +
		"other private matters. The desk is a roll top type " +
		"and is polished to a deep shine. On it you see some " +
		"parchments, an ink well, and some writing quills.\n");
	add_item("parchments",
		"As you examine the parchments, you see they are finely " +
		"grained papers with delicate designs acrossed the top " +
		"and bear her ensignia.\n");
	add_item("ink well",
		"A small container filled with ink.\n");
  	add_item("quills",
		"Some writing quills sit here.\n");

    add_exit( TCASTLE_DIR + "q_dr",   "east");
    add_exit( TCASTLE_DIR + "q_room", "west");
}


void
reset_room()
{
}
