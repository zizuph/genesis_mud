/*
 * Private Board room
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
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");

    set_short("Private Discussion Cavern");
    set_long(short() + ". The cavern is has been enlarged. The walls are smooth and polished. There are veins that flow through the walls and seem to pulse with life. A large board sits in the center of the cavern. It's where drow can discuss adventures and events.\n");

if (!objectp(board))
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name(BOARD_RA_DIR);
        board->move(this_object());
    }

    add_item(({"board", "large board"}),
        "It's a large piece of stone. It is ornately carved and set in the center of the room. Notes are attached to it for anyone to read. The board is limned in faerie fire, which makes it glow in the darkness.\n");

    add_exit("admin", "northeast");
    add_exit("start", "east");
    add_exit("po", "south");
    add_exit("join", "west");
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

int
check_matron()
{
   
   object tp = this_player();
   
   if((tp->query_wiz_level()) || (check_drow(TI, HOUSE_MATRON))) return 0;
      
    write("Only Matron Mothers may go there.\n");
      return 1;

}
