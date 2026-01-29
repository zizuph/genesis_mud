/**********************************************************************
 * - dragoman: The dragoman station and Tyr board room.             - *
 * - Increased board notes from 50 to 99.                           - *
 * - Being a bit nostalgic so would like to keep notes a bit longer - *
 * - Updated by Damaris@Genesis 06/2006                             - *
 **********************************************************************/


inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

static void
create_board()
{
	object board;
	if((board = clone_object("/std/board")))
	{
		board->set_board_name(TYR+"board");
		board->set_num_notes(99);
		board->set_silent(0);
		board->set_err_log(TYR+"board/errors");
		board->set_show_lvl(0);
		board->move(TO);
	}
	return 0;
}

public void
reset_room()
{
	if(!present("board", TO))
	create_board();
}

void
create_room()
{
	::create_room();
	object board;
	set_short("draqoman station");
	set_long("This building serves as the rendez-vous point for the "+
	"draqomen of Tyr. Serving as guides (among other things) "+
	"to newcomers, the draqomen have more information on the "+
	"city than possibly even the Templars, and unlike them are "+
	"willing to share their knowledge: For a price.\n");
	
	add_exit(TYR_CARAVAN+"rd_cw_02.c", "north", 0, 1);
	add_exit(TYR_CARAVAN+"common.c","down",0,1);
	reset_room();
}
