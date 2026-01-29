
/* 
	*Passageway in the orc guild caves, board room
	*Altrus, May 2005
*/
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include "/d/Shire/guild/orc_guild/orc.h" 
#include <std.h>

inherit "/d/Shire/std/room";

static void create_board();

void create_shire_room()
{
	set_short("Inside a damp, dark cave");

	set_long(short() + ". A dull light, which comes from a few weak torches lining the walls, allows you to find your way. A distinct feeling of furtive watchfulness fills the cave. There appears to be a room to the east of here, while the main passage heads north.\n");
	
	add_item(({"cave"}), "There is not doubt that this part of the cave has been cut and dug out by tools; the walls are too square to be natural.\n");
	add_item(({"walls"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to head heighth. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"torches", "small torches", "weak torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of small sticks. They barely shed any light on the cave.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"room"}), "From where you are standing, not much can be seen from the room east of here. The light in there looks a bit brighter than the light in the passage.\n");
	add_item(({"passage"}), "The main passage of the cave runs north and southeast from here.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	
	add_exit("/d/Shire/guild/orc_guild/rooms/entry2", "southeast");
	add_exit("/d/Shire/guild/orc_guild/rooms/passage2", "north");
	
	reset_shire_room();
}

void reset_shire_room()
{
    if (!present("board", TO))
        create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/d/Shire/std/board")))
    {
        board->set_board_name(ORCGLD_DIR + "board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("You may not do that.\n");
        board->move(TO);
    }
    return 0;
}
