inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include "sw.h"

init()
{
	::init();
	add_action("enter_shrine","down");
	add_action("enter_shrine","d");
	add_action("enter_shrine","east");
	add_action("enter_shrine","e");
	add_action("enter_shrine","enter");
}

create_room()
{
	set_short("Arrival chamber");
	set_long("You stand in the arrival chamber of the"
		+" guild and home of the Spellweavers.  The walls here are a"
		+" dark, polished stone that seems to absorb what little light there"
		+" is, extending the shadows.  You wonder what watchful force"
		+" might be lurking in the corners.  It is very quiet here, a kind of"
		+" chill hush that, to strangers, is discomforting; to"
		+" those who reside here, however, it is the dark embrace of"
		+" those forces which they serve, and which, in turn, serve them, at"
		+" their call.  You may pass under carved stone archways to the"
		+" north and south.  On the east side of the room, a few"
		+" steps descend into a larger room, apparently lit by torches"
		+" in sconces along the walls.\n");

	add_exit(SWG+"hallnw","north",0);
	add_exit(SWG+"hallsw","south",0);

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 1);

	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago.\n");
	add_item(({"corner","corners"}),"Peering into the corners of"
		+" this shadowy chamber, you can see nothing; yet you are unable to"
		+" shake the feeling that some dark force watches over you, and over"
		+" this place.\n");
	add_item(({"archway","archways"}),"The exits from this"
		+" chamber lead north and south, passing beneath stone"
		+" archways carved with many small runes.\n");
	add_item("runes", "You stare for a time at the"
		+" hundreds of tiny runes carved into the stone here."
		+"  They are undecipherable, however, having their origins"
		+" lost in a time centuries ago.\n");

}

enter_shrine()
{
	if ( !(TP->query_guild_member("Spellweavers")) && !TP->query_prop("_sw_i_am_invited_"))
	{
		write("Non-members"
			+" are not allowed into the unholy shrine"
			+" of the Spellweavers unless invited in by a"
			+" sponsor.\n");
	}
	else
	{   
		TP->catch_msg("You step into the shrine.\n");
		tell_room(environment(), QCTNAME(TP) + " leaves down into the shrine.\n", TP);
		TP->move_living("",SWG+"shrine");
	}
	return 1;
}

