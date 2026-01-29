/*
* Modifier version of the
* Post Office in the Tower of Wayreth.
* 
*/

#include "../local.h"
#include <stdproperties.h>

inherit "/d/Ansalon/std/room";

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
   set_short("Post Office");
   set_long("This is a small corner of the grotto, that is dedicated to sending "+
            "messages in and out of the Pirate hideout. You see a large shaft "+
            "in the cave leading out into the open, over the sea. "+
            "There are also several Albatros' that have small containers tied "+
            "to their legs, so they can carry the messages Pirates might "+
            "want to send. Infront of you is a small desk with a quill and "+
            "paper ready for you to write the letters you want. \n");
   
   add_prop(ROOM_I_INSIDE, 1); // we are inside the cave
   add_exit("pirate_center_room","northeast",0);
}

void
init()
{
   object mr;
   string *conclave;
   
   ::init();
   
   mr = clone_object("/secure/mail_reader");
   
   
   mr->move(this_player(), 1);
}

void
leave_inv(object ob, object to)
{
   object reader;
   
   ::leave_inv(ob, to);
   
   reader = present(MAILREADER_ID, ob);
   
   if (reader)
      reader->remove_object();
}

int
query_mail(int silent)
{
   string new;
   int mail;
   
   mail = MAILCHECKER->query_mail();
   
   if (!mail) return 0;
   
   if (silent) return 1;
   
   new = "";
   if (mail == 2) new = " NEW";
   if (mail == 3) new = " unread";
   
   write("\n" +
      "There is" + new + " mail for you in the " +
      "post office in the Pirate guild.\n\n");
   
   return 1;
}                                                

