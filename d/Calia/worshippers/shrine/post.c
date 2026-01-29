/* Original File: /d/Genesis/start/human/town/post.c 

  Modified by Quintas		23 Apr 03
  - commented out south exit from this room.

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

    if (objectp(ob) && ob->query_wiz_level())
    {
        // Wizards should not have their mail readers removed.
        return;
    }

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

    add_exit(WOR_SHRINE+"common","north");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
