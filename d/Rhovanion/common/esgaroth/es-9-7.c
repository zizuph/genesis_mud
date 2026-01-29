inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>

string messages;
int new_mail;

create_room() 
{
	add_exit("/d/Rhovanion/common/esgaroth/es-8-7","west");
    set_short("Esgaroth Post office");
    set_long("You are in the Esgaroth post office.  Commands:\n"+
		"read            Read from the mailbox.\n" +
		"mail <name>     Mail to player 'name'.\n" +
		"from            List all headers.\n"
	);
}

init() 
{
    ::init();
    clone_object("/secure/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to)
{
    object reader;
    ::leave_inv(ob);

    reader = present("mailreader", ob);
    if (reader)
        reader->remove_object();
}
