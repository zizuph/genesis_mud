inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

object board;

create_room()
{
	set_short("Public board room");
	set_long("You have entered the public board"
		+" room of the Spellweavers' guild home. This board is"
		+" intended for outsiders wishing acceptance into our"
		+" ranks to post their notices requesting sponsorhip,"
		+" after which a sponsor may or may not contact them."
		+" You may depart this room by heading south.\n");
	
	add_exit(SWG+"depart","south",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE,1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago.\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	
	if(!present("board",TO))
	{
		board=clone_object("/std/board");
		board->set_board_name(SWG+"boards/public");
		board->set_num_notes(20);
		board->set_no_report(1);
		board->set_silent(0);
		board->move(TO);
	}	
}
