/*
* Post Office in the Tower of Wayreth.
*
* By Rastlin 950523
*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
   set_short("Post Office");
   set_long("You are standing in a small post-office in the " +
      "town of Flotsam. Here you can send mail to anyone in the " +
      "realm of Genesis, or read your own mail. \n");
   
    add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(FROOM + "street43","north",0);
}

void
init()
{
    object mr;
    string *conclave;
   
    ::init();

    if (!interactive(TP))
       return;
   
   mr = clone_object("/secure/mail_reader");
   mr->move(TP, 1);
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
      "post office in the Tower of Wayreth.\n\n");
   
   return 1;
}                                                


