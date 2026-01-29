inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
string messages;
int new_mail;

create_room()
{
   ::create_room();
   hear_bell = 2;
   INSIDE;
   set_short("The post-office of Kabal");
   set_long("This is the post-office of Kabal, where you "+
      "can both read letters from far away, and send them there too. "+
      "The building is made of stone, giving it a lasting look "+
      "and contains, except from some tables, a small sign on the wall.\n");
   add_item("sign","@@sign");
   add_item("table","This is where you can sit down and write or "+
      "read your letters. Its littered with papers and feather pens.\n");
   add_cmd_item("sign","read","@@sign");
   add_exit(CENTRAL(plaza/sq_south),"northeast",0,-1,-1);
   add_exit(CENTRAL(plaza/sq_pigeon),"west",0,-1,-1);
}
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
