inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)

string messages;
int new_mail;

create_room()
{
   ::create_room();
   INSIDE;
   set_short("The post-office of the Shadow Walkers");
   set_long("You are now in a dark alcove. There is a small "+
   "table and chair. On the table are writing impliments. "+
   "Here, you can send and recieve mail from all over the "+
   "world. A single torch burns on one wall, casting "+
   "strange shadows across the room.\n");
   add_item("table","A small wooden table. There is a pen, and a stack "+
   "of papers here.\n");
   add_item("torch","It burns dimly, making shadows flicker around.\n");
   add_item("chair","A hard, wooden chair for you to sit on when you "+
   "write.\n");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit("/d/Kalad/common/guilds/shadow_walkers/t12","south",0,-1,1);   
}

string
sign()
{
   return "In this post office you can do the following\n"+
   "read:          Read from the mailbox.\n"+
   "mail <name>:   Mail to <name>.\n"+
   "from:          List all headers.\n";
}

init() {
   ::init();
   clone_object("/secure/mail_reader")->move(TP,1);
}


leave_inv(ob, to)
{
   object reader;
   ::leave_inv(ob);
   
   reader = present("mailread", ob);
   if (reader) reader->remove_object();
   
}

