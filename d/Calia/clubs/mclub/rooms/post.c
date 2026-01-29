/* Original File: /d/Genesis/start/human/town/post.c 

*/
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"

#define MAILREADER       "/secure/mail_reader"

string messages;
int new_mail;

init()
{
    object reader;
    string *r;
    ::init();

    seteuid(getuid());
    reader = clone_object(MAILREADER);
    if(!reader)
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

leave_inv(ob, to)
{
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}


void
create_room()
{
 
    set_short("The shrine post office");
    set_long("This chamber appears to be a post office.  It is "+
        "very quiet, and has private booths for you to read or "+
        "write mail to others in this world.\n"+
        "Commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    from            List all headers.\n"+
        "");

    add_exit(ROOM_DIR+"shconcon","southwest",0,1);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
