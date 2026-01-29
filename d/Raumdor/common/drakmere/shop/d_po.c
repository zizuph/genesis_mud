#include "defs.h"
inherit STD_ROOM;
string messages;
int new_mail;

create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
   ::create_room();
   set_short("The post-office of Drakmere");
   set_long("This is the post-office of Drakmere, where you can "+
   "send mail around the world. The room is rather sparse, with a "+
   "few tables and chairs. A sign on the wall reads:\n"+
   "In this post office you can do the following:\n"+
   "read          Read from the mailbox.\n"+
   "mail <name>   Mail to <name>.\n"+
   "from          List all headers.\n");
   add_item(({"tables","chairs"}),"This is where you can sit down and write "+
   "or "+
      "read your letters. Its littered with papers and feather pens.\n");
   add_exit(DRAKMERE_DIR + "road15","south",0);
   add_exit(DRAKMERE_DIR + "road16","southeast",0);
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

int *
query_coordiantes()
{
    return ({65, 3, 0});
}
