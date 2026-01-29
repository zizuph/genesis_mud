#include <stdproperties.h>
#include "../edefs.h"

inherit WATER_ROOM;

#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER	"/secure/mail_checker"

void create_room()
{
    set_short("Coral Requiem Post Office");
    set_long("   This is the post office of Coral Requiem.  Special care " +
        "must be taken so that the mail is not damaged by the water.  " +
        "Here you can mail people all over the world.\n" +
        "\nCommands are:\n" +
            "    read           Read your mail.\n" +
            "    mail <name>    Mail to player 'name'.\n" +
            "    from           List all mail headers.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);

   add_exit(CRDIR+ "cr25", "southeast");
}

void init()
{
   object reader;
   
   ::init();
   reader=clone_object(MAILREADER);
   if (!reader) {
      write("No mailreader is available at this time.\n");
      return;
   }
   reader->move(this_player(), 1);
}

void leave_inv(object ob,mixed to)
{
   object reader;
   
   ::leave_inv(ob,to);
   while (reader=present("mailread",ob))
   {
     reader->remove_object();
   }
}

int query_mail(int silent)
{
    int mail;

    if (!(mail = MAILCHECKER->query_mail()))
	return 0;
    if (silent)
       return 1;

    write("\nThere is" + (mail > 1 ? " NEW" : "") + 
        " mail for you in the Coral Requiem post office.\n");
    return 1;
}
