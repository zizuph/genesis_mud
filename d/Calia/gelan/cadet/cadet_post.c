
/* 

   ~Calia/gelan/cadets/post.c

   Post room of the Cadets of Gelan. 

   Adapted by Maniac@Genesis from standard post office code.

*/

#pragma save_binary

inherit "/std/room";
#include "cadet.h"
#include <stdproperties.h>

#define MAILREADER       "/secure/mail_reader"

int
gc_query_private_room()
{
    return 1;
}

void
init()
{
    object reader;

    ::init();

    seteuid(getuid());
    reader = clone_object(MAILREADER);
    if(!objectp(reader))
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}


/* Take away the mailreader */
void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);

    reader = present("mailread", ob);
    if (objectp(reader)) reader->remove_object();
}


void
create_room()
{
    set_short("Cadet post office");
    set_long(
	"Post office of the " + GC_GUILD_NAME + ".\n" + 
        "Commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    from            List all headers.\n"+
        "");

    add_prop(ROOM_I_INSIDE, 1);
      
    add_exit(GC_STARTROOM, "north"); 
}

