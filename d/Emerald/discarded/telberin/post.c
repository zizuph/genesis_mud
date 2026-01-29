inherit "/std/room";
 
#include "default.h"
#include <stdproperties.h>
#include "default.h"
 
#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER     "/secure/mail_checker"
 
void
create_room()
{
    set_short("Royal Post Office of Telberin");
    set_long("   The post office of Telberin is a marvel in " +
        "the city. It's quick and efficent and never ceases to " +
        "astound the elves. From here, you may send messages " +
        "to anyone in Emerald or to foreign lands. Several " +
        "elves busily work here sorting all of the mail that " +
        "comes in and goes out. To make it easier for them, " +
        "the Head Postmaster of Telberin has posted a sign " +
        "on the wall.\n\n");

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
    add_item(({"elves", "elf"}),
        "The elves are hurridly sorting all the mail that " +
        "needs to be delivered. They don't have time to talk " +
        "to you.\n");
    add_item ("head postmaster",
        "He's supervising his employees, making sure " +
        "they do their work properly.\n");

 
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(AVENUE_DIR + "ave22", "out");
}
 
init()
{
    object reader;
   
    ::init();
    reader=clone_object(MAILREADER);
    if (!reader) 
    {
        write("No mailreader is available at this time.\n");
    return;
    }
    reader->move(this_player());
}
 
leave_inv(object ob,mixed to)
{
    object reader;
   
    ::leave_inv(ob,to);
    reader=present("mailread",ob);
    if (reader)
        reader->remove_object();
}
 
query_mail(int silent)
{
    string new, sp;
    int mail;
 
    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;
    if (silent)
        return 1;
    new="";
    sp="    ";
    if (mail>1) 
    {
        new=" NEW";
        sp="";
    }
    write("\nThere is"+new+" mail for you in post office of Telberin.\n");
    return 1;
}

string
read_sign()
{
    return   "          Common commands are:\n" + 
             "          read           Read your mail.\n" +
             "          mail <name>    Mail to player 'name'.\n" + 
             "          from           List all mail headers.\n\n" +
             "Examine the mailreader for more commands.\n";
}
