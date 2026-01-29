/*
*   The Hin Warriors own post-office.
*/

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/d/Shire/buckland/buckdefs.h"

string messages;
int new_mail;

create_room() {
   set_short("The post office of Bree-Hill");
   set_long("@@my_long");
   
   add_item(({"mailboxes","mailbox","hole","holes","little holes"}),
      break_string("The little holes are mailboxes. In some are letters, "
         + "others are just empty.\n",70));
   
   add_exit(BB_DIR + "buroad9","east");
   
   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

my_long() {
   string long;
   long = "You have entered a hobbit-hole of some sort, with many little boxes \n"
   + "on the wall. The Buckland division of the Bounders of the Shire is\n" 
   + "day and night busy here, to keep the mail from all over Genesis\n"
   + "flowing in. Pigeons and horseback riders take outgoing mail to places all\n"
   + "over the world. Other people are just sorting the mail into the\n"
   + "small mailboxes.\n"
   + "Available commands are:\n"
   + "from             Examine all headers of your incoming mail\n"
   + "read             Start reading your incoming mail.\n"
   + "mail <name>      Mail to another player with the name 'name'.\n";
   return long;
}

enter_inv(ob, from)
{
   ::enter_inv(ob, from);
   if (from == this_room()) return;
   if (present("mailreader", ob)) return;
   clone_object("/secure/mail_reader")->move(ob);
}

leave_inv(ob, to)
{
   object reader;
   
   ::leave_inv(ob, to);
   if (to == this_room()) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}

query_mail(silent) {
   string name;
   string new;
   
   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "********************************************************\n"+
      "There is"+new+" mail for you in the nearest post office.\n"+
      "********************************************************\n\n");
   return 1;
}
