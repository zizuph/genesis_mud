/*
* Modifier version of the
* Post Office in the Tower of Wayreth.
* 
*/

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>

inherit MITHAS_OUT;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
   set_short("Post Office");
   set_long("You are standing in a small post-office in the " +
      "city of Nethosak. This small room is made out of "+
      "dark-grey stone and only a few furnitures "+
      "have been put into this place. It's actually quite "+
      "amazing since you can send mail to anyone in the " +
      "realm of Genesis, or read your own mail. \n"); 
   
   add_exit(MROOM + "road39","west",0);
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
      "post office in the city of Nethosak.\n\n");
   
   return 1;
}                                                

