/*
 * The Frogmorton Post Office
 * Code from Bree PO by Kesor, June 1998
 * Modified by Finwe, September 1998
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"
 
inherit SHIRE_ROOM;
 
string Messages;
int New_mail;
 
void
create_shire_room()
{
    set_short("Frogmorton Messenger Service");
    set_long("This quiet building is the Messenger Service of " +
        "Frogmorton. Hobbits come here to send letters to all " +
        "over the Shire and receive news from afar from those " +
        "they know. The place is busy with all the sorting and " +
        "shuffling of messages that flow through this service. " +
        "Fortunately the hobbits like receiving messeges so they " +
        "don't mind the work.\n\n" +
        "Available commands are:\n"+
        "from             Examine all headers of your incoming mail\n" +
        "read             Start reading your incoming mail.\n" +
        "mail <name>      Mail to another player with the name 'name'.\n"+
        "You can learn more by studying your mailreader.\n");
 
    add_item(({"mailboxes", "mailbox", "hole", "holes", "little holes"}),
        "The little holes are mailboxes. In some are letters, " +
        "others are just empty.\n");
   
    add_exit(FROG_DIR + "road03", "out",0,0,1);
    add_exit(FROG_DIR + "road03", "east");    
   
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
