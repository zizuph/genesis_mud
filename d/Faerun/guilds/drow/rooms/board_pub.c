/*
 * Public Board room
 * By Finwe, May 2006
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";


void
create_drow_room()
{
    object board;

    setuid();
    seteuid(getuid());

    set_short("Public Discussion Cavern");
    set_long(short() + ". The cavern is irregular shaped but has been enlarged. The walls are smooth and polished and the veins in the rock seem to pulse with life.  A large board is set in the center of the room. It serves as a place where outsiders may discuss their adventures.\n");

if (!objectp(board))
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name(BOARD_PU_DIR);
        board->move(this_object());
    }

    add_item(({"board", "large board"}),
        "It's a large piece of stone. It is ornately carved and set in the center of the room. Notes are attached to it for anyone to read. The board is limned in faerie fire, which makes it glow in the darkness.\n");

    add_exit("join", "south");
}
    

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

}

/* Just a helper function to verify someones rank. */
private int
check_drow(mixed who, int rank)
{
    if (objectp(who))
	who = who->query_real_name();
    else
	who = lower_case(who);

    return GSERVER->query_member(who, rank);
}
