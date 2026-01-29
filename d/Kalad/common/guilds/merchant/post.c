inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
string messages;
int new_mail;
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("The private post office of the Merchants Guild");
   set_long("This is the private post office of the Merchants Guild of "+
      "Kabal.\n"+
      "read            Read from the mailbox.\n" +
      "mail <name>     Mail to player 'name'.\n" +
      "from            List all headers.\n"
   );
   add_exit(CVAN(guild/hall2),"east",0,-1,-1);
}

init() {
   ::init();
   clone_object("/secure/mail_reader")->move(TP,1);
}

leave_inv(ob, to) {
   object reader;
   ::leave_inv(ob);
   
   reader = present("mailread", ob);
   if (reader) reader->remove_object();
   
}
