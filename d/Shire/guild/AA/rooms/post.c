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
  set_short("The post office");
  set_long("This is the post office of Angmar's Army. Here they collect "+
        "the letters from all over the world. Therefore you may be able to "+
        "read your post here. You can also send a letter from here. It will "+
        "be delivered to every known post and so you can be confident that "+
        "it will reach the right address.\n"+
        "Available commands are:\n"+
        "    read            Read your mail.\n"+
        "    mail <name>     Mail to player 'name'.\n"+
        "    from            List all headers.\n"+
        "");

  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  add_exit(AA_DIR+"rooms/c1", "east");
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
