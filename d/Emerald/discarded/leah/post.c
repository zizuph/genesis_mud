
inherit "std/room";

#include <stdproperties.h>
#include "/d/Emerald/defs.h"

#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER"/secure/mail_checker"

void create_room()
{
   set_short("Post Office");
   set_long("   This is the post office.  Special care " +
      "must be taken so that the mail isn't torn or lost.  " +
      "Here you can mail people all over the world.\n" +
      "\nCommands are:\n\n" +
      "    read           Read your mail.\n" +
      "    mail <name>    Mail to player 'name'.\n" +
      "    from           List all mail headers.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(VILLAGE_DIR+ "road2", "east");
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
