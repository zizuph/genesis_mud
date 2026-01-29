#include "defs.h"

inherit TRICKSTER_STD_ROOM;

void create_room()
{
 set_short("A crude hallway");
 set_long(BS(
   "A crude hallway has been dug here.  It's much drier and more "+
   "livable than some of the other rooms around here.  You notice a "+
   "sign pointing east in the middle of the room as well there are "+
   "rows of torches which line this hallway providing some warmth. "+
   "This hallway breaks off to the east and continues to the south , "+
   "while to southwest you see kind of office.\n"));

 add_item(({"torch","torches"}),"These torches burn brightly in the "+
   "room providing light.\n");
 add_item("sign","Ummm maybe you should try reading it?\n");
 add_cmd_item("sign","read","Alchemist shop:  Enter at your own risk!\n");

 add_exit(TRICKSTERS+"train","northwest");
 add_exit(TRICKSTERS+"hall_end","south");
 add_exit(TRICKSTERS+"shop","east");
 add_exit(TRICKSTERS+"office","southwest","@@block");
}

void init()
{
 ::init();

 add_action("do_become","become");
}

int do_become(string what)
{
 object shadow;

 NF("Become what?!? A trickster maybe???\n");
 if(!what || what!="trickster") return 0;

 shadow = clone_object(TRICKSTERS_SHADOW);
 if (shadow->add_trick_shadow(TP) != 1)
  {
   shadow->remove_shadow();
   write("Hmm... The gods don't want you to join this Order.\n" +
     "Perhaps you're already a member of another layman guild?\n");
   return 1;
  }
 
 write("Welcome to Tricksters!!!\n");
 return 1;
}

int block()
{
 if((SERVER)->query_jamadar(TP->query_name()) ||
    (SERVER)->query_leader(TP->query_name())) return 0;

 write("Only Jamadars allowed to enter the office.\n");
 return 1;
}

