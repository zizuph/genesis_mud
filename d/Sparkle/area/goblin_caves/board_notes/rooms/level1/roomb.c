/*
 * Board room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

void make_board();

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();
    set_short("Board room");
    set_long("This is a small room with a bulletin board that can be " +
             "used by adventurers who want to begin discussions or make " +
             "suggestions. You see sleeping quarters to the west and a " +
             "big stair to the east.\n\n");

	add_item("stairs", "You should go closer to see any details.\n");
	add_item(({"wall", "walls"}), "You can see poster on the northern wall.\n");
	add_item("poster", "Read it.\n");
	add_item(({"sleeping quarter", "sleeping quarters"}),
	         "You should go west to get there.\n");
	add_item(({"stairs", "big stairs", "stair", "big stair"}),
	         "You should go east to get there.\n");

    add_cmd_item( "poster",
                  "read",
                  "Poster says: \"Bulliten board for comments about these " +
                  "goblin caves.\".\n");

    add_exit ("roomc", "east");
    add_exit ("rooma", "west");
    add_exit ("roome", "south");

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());

    setuid();
    seteuid(getuid());

    make_board();

    reset_room();
} /* create_room */


/*
 * Function name:        make_board
 * Description  :        set up the bulletin board
 */
void
make_board()
{
    object  bboard;

    bboard = clone_object(BOARD_DIR + "l1_board");

    if (bboard)
    {
        bboard->move(this_object());
    }
    else
    {
		add_my_desc("ERROR: Board not created. Please mail a wizard.\n");
	}
} /* make_board */
