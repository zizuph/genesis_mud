#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define MAILREADER     "/secure/mail_reader"
#define MAILCHECKER    "/secure/mail_checker"

void
create_room()
{
  set_short("The Council Post Office");

    set_long("This is the private post office for the council members " +
        "of the Army of Angmar. Here, they can  read and answer letters " +
        "sent to them from all over the world, and do so privately.\n" + 
        "Available commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    from            List all headers.\n"+
        "");

  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  add_exit(AA_DIR+"rooms/council", "west");
}

void
init()
{
    object reader;
    ::init();

    reader = clone_object(MAILREADER);
    if (!reader) {
        write("No mailreader is available at this time.\n");
        return;
    }
    reader->move(this_player());
}

void
leave_inv(object ob,object to)
{
    object reader;
    ::leave_inv(ob, to);

    reader = present("mailread", ob);
    if (reader) reader->remove_object();
}

int
query_mail(int silent) 
{
    string new, sp;
    int mail;

    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;
    if (silent)
        return 1;
    new = ""; sp = "    ";
    if (mail>1) {
        new = " NEW";
        sp = "";
    }
    write("\n"+
        "     +-------------------------------------------------------+\n"+
        "     !    There is a"+new+" mail for you.                    "+
        sp +"   !\n"+
        "     ! You can read it in Angmar's Army post office.         !\n"+
        "     +-------------------------------------------------------+\n");
    return 1;
}
