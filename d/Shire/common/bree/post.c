/*
*   The Bree post-office.
*/

inherit "/d/Shire/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

string messages;
int new_mail;

create_room() {
    set_short("The post office of Bree-Hill");
    set_long("@@my_long");
   
    add_item(({"mailboxes","mailbox","hole","holes","little holes"}),
        "The little holes are mailboxes. In some are letters, " +
        "others are just empty.\n");
   
    add_exit(BREE_DIR + "middle","west");
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

}

my_long()
{
    string long;
    long = "You have entered a hobbit-hole of some sort with many " +
        "little boxes on the wall. The workers here are busy here " +
        "day and night to keep the mail from all over Genesis " +
        "flowing in. Pigeons and horseback riders take outgoing " +
        "mail to places all over the world. Other people are just " +
        "sorting the mail into the small mailboxes.\n";
   return long;
}

enter_inv(ob, from)
{
   object reader;
   object vote_room;
   string *masters;

   ::enter_inv(ob, from);

    if (!living(ob))
        return;
   if (present("mailreader", ob)) return;
   reader=clone_object("/secure/mail_reader");
   reader->move(ob, 1);
}

leave_inv(ob, to)
{
   object reader;
   
   ::leave_inv(ob, to);
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
