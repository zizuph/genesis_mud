/*
 * The Longbottom Post Office
 * Finwe, December 2019
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
 
inherit SHIRE_ROOM;
 
string Messages;
int New_mail;
 
void
create_shire_room()
{
    set_short("Longbottom Post Office");
    set_long("This quiet building is the Post Office of Longbottom. " +
        "Messages from all all over the world are delivered here. This " +
        "is a busy place as " +
        "messages are sorted and delivered to hobbits of Longbottom. " +
        "Luckily, this doean't bother them as they are anxious " +
        "for news.\n\n" +
 
        "Available commands are:\n"+
        "from             Examine all headers of your incoming mail\n" +
        "read             Start reading your incoming mail.\n" +
        "mail <name>      Mail to another player with the name 'name'.\n"+
        "You can learn more by studying your mailreader.\n");
 
    add_item(({"mailboxes", "mailbox", "hole", "holes", "little holes"}),
        "The little holes are mailboxes. Some of the mailboxes are full " +
        "of messages, others are partially full, and a few are empty.\n");
   
    add_exit(LB_RM_DIR + "lb04", "out",0,0,1);
    add_exit(LB_RM_DIR + "lb04", "southwest");    
   
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}
 
void
enter_inv(object ob, object from)
{
    object reader;
 
    ::enter_inv(ob, from);
 
    if (!living(ob))
         return;
 
    if (present("mailreader", ob))
        return;
    reader = clone_object("/secure/mail_reader");
    reader->move(ob);
}
 
void
leave_inv(object ob, object to)
{
    object reader;
   
    ::leave_inv(ob, to);
    reader = present("mailreader", ob);
    if (reader)
        reader->remove_object();
}
 
int
query_mail(int silent)
{
   string name;
   string new;
   
   name = lower_case(TP->query_name());
   if (!restore_object("/d/Genesis/post_dir/" + name) || Messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (New_mail)
      new = " NEW";
   write("\n"+
      "***********************************************************\n"+
      "There is" + new + " mail for you in the nearest post office.\n"+
      "************************************************************\n\n");
   return 1;
}
