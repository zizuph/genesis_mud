inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"

object board;

create_room()
{
	set_short("Private board room");
	set_long("This is the board room for members of"
		+" the guild of the Spellweavers.  It is intended for the"
		+" discussion of ideas and issues pertaining to the guild and"
		+" its members (whereas the public board located elsewhere in"
		+" the guild is for prospective members to request sponsorship)."
		+"  You may leave this room back to the north.\n");
	
	add_exit(SWG+"strune_","north",0);
	add_exit(SWG+"com_board","common",0);
	
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
	
	if(!present("board",TO)) {
		board=clone_object("/std/board");
		board->set_board_name(SWG+"boards/private");
		board->set_num_notes(30);
		board->set_no_report(1);
		board->set_silent(0);
		board->move(TO);
	}	
}

