inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

string messages;
int new_mail;

create_room() 
{
    add_exit("/d/Rhovanion/common/rhun/sw/guild/psrune_","southeast");
    set_short("Guild Post office");
    set_long("You are in the post office in the home of the Spellweavers.  Commands:\n"+
		"read            Read from the mailbox.\n" +
		"mail <name>     Mail to player 'name'.\n" +
		"from            List all headers.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
}

init() 
{
    ::init();
    clone_object("/secure/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to) 
{
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();
}
