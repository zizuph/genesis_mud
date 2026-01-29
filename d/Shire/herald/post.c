/*
*   The Heralds of the Valar own post-office.
*/

#pragma save_binary

inherit "/d/Shire/room";

#include "/sys/stdproperties.h"
#include "herald.h"

string messages;
int new_mail;

void
create_room()
{
   set_short("A side branch of a large maple tree");
   set_long("@@my_long");
   
   add_item(({"mailboxes","mailbox","hole","holes","little holes"}),
      break_string("The little holes are mailboxes. In some are letters, "
         + "others are just empty.\n",70));
   add_item(({"pigeon","pigeons","seagull","seagulls","gulls","gull"}),
   "They eye you expectantly, eager to spread their wings.\n");
   
   add_exit(HERALD_DIR + "board","down");
   add_exit(HERALD_DIR + "start","up");
   

}

string
my_long()
{
   string long;
   long = "On the main trunk of the great maple tree are some "+
   "pigeons and seagulls waiting to take your mail all across "+
   "the world.  Down leads to the conversation room, and up "+
    "leads farther up the tree.\n"
   + "Available commands are:\n"
   + "from             Examine all headers of your incoming mail\n"
   + "read             Start reading your incoming mail.\n"
   + "mail <name>      Mail to another player with the name 'name'.\n";
   return long;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    if (present("mailreader", ob)) 
        return;

   clone_object("/secure/mail_reader")->move(ob, 1);
}

void
leave_inv(object ob, object to)
{
   object reader;
   
   ::leave_inv(ob, to);
   reader = present("mailreader", ob);
   if (reader && !ob->query_wiz_level()) reader->remove_object();
}

query_mail(silent)
{
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
      "There is"+new+" mail for you in the Post of the Heralds of the Valar.\n"+
      "********************************************************\n\n");
   return 1;
}
