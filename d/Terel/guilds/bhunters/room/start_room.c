/*
 Bounty hunters training room,
 by Udana 05/06
 temp also join room.
*/

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../bhunters.h"
#include <files.h>

inherit "/lib/guild_support";

inherit BHROOM + "bhroom";

string room_long()
{
	return "This room is free to use for bounty hunters in need. Besides standard room equipment, there is "+
		"a matting on the floor, right next to the table.\n";
}

public void create_bhroom()
{
	add_exit(BHROOM + "corridor2", "east", 0, 1, 0);
	add_item("matting", "Matting, large enough to sit on it comfortably. Suitable for meditating.\n");
	
}

public void leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 


public void init()
{
	::init();
	init_guild_support();
	add_action("start", "start");
}

int start(string str)
{
	if(!TP->query_guild_member(BHNAME))
	{
		notify_fail("This room was reserved for visiting bounty hunters only.\n");
		return 0;
	}
	if(TP->set_default_start_location(BHROOM + "start_room"))
	{
		write("You'll decide to stay in 'Hook & Dagger' for a while.\n");
		return 1;
	}
	else
	{
		notify_fail("Mail GM, or Terel Liege about that!\n");
		return 0;
	}
}