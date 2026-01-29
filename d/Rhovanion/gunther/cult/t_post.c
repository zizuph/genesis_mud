inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

string messages;
int new_mail;

create_room()
{
	set_short("Guild Post office.");
	set_long("Here a few novices run the post office of the Cult. Commands are :\n"+
					"read            Read from the mailbox.\n" +
					"mail <name>     Mail to player 'name'.\n" +
					"from            List all headers.\n");
	
	add_item(({ "novices", "novice" }), "Bound to an oath of silence as they are,"
		+" none of them can or will speak to you.\n");
		
	add_exit(CULT_DIR + "t_gather","southwest", 0);
	add_exit(CULT_DIR + "t_shop", "south", 0);

	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_LIGHT,1);
}

init()
{
	::init();
	clone_object("secure/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to)
{
	object reader;
	::leave_inv(ob); /* , to); */
	
	reader = present("mailread", ob);
	if (reader) reader->remove_object();
}
