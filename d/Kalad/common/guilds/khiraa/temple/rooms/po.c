inherit "/d/Kalad/room_std";
inherit "/d/Genesis/lib/post";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

#pragma strict_types
#pragma save_binary

void
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The messenger room of the Khiraa");
   set_long("\n   You are in a small chamber that is almost bare. "+
   "There is a small table here, along with a chair. In the "+
   "corner of the room, you see a small brazier, burning an eerie "+
   "purple flame. A sign is pinned to the wall.\n\n");

   add_item("table","A small wooden table. There is a pen, and a stack "+
   "of papers here.\n");
   add_item("chair","A hard, wooden chair for you to sit on when you "+
   "write.\n");
   add_item("brazier","It is made of black steel, and it burns a "+
   "strange purple light.\n");

   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit(KHIRAA_DIR(temple/rooms/t11),"south",0,-1);
}

string
sign()
{
   return "In this post office you can do the following\n"+
   "read:          Read from the mailbox.\n"+
   "mail <name>:   Mail to <name>.\n"+
   "from:          List all headers.\n";
}

void
init() 
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob);
    post_leave_inv(ob,to);
}

void
mail_message(string new)
{
    write("\n"+
    "A soft voice whispers to you that there is"+new+" mail waiting "+
    "for you in the Temple post office.\n\n");
}
