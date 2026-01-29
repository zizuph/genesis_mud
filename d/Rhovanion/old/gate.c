inherit "/std/room";
#include "def.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.c"

object gateguard1,gateguard2;

void create_room()
{
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,1);
   set_short("Gate of Thranduil's Caverns");
   set_long(break_string("You are standing at the gates of Thranduil's "
         + "Caverns, as you look farther in you see "
         + "some great halls. They do remind you of "
         + "the stories you heard as a child about "
         + "Menegroth and Gondolin of old. There is "
         + "a sign here with some writing upon it. "
         + "You can choose to go back to the southeast "
         + " or go north past the gates. \n",70));
   
   add_item("gate",break_string("This is a sturdy, magic looking gate, "
         + "it looks like it is impossible to "
         + "break it down, or open it without "
         + "the accept of Thranduil, King of "
         + "the Caverns. \n", 70));
   
   add_exit(THIS_DIR + "cave1","north",0,1);
   add_exit(THIS_DIR + "w1","southeast",0,1);
   call_out("reset_room",1);
}

void
reset_room()
{
   call_out("reset_room1",1);
   call_out("reset_room2",1);
}

void
reset_room1()
{
   gateguard1 = present("gateguard1");
   if(gateguard1 && gateguard1->queryname() != "eldaran" && gateguard1->queryname() != "corpse")
      return;
   else
      gateguard1 = clone_object("/d/Rhovanion/common/npcs/elves/gateguard1");
   gateguard1 -> move_living("into a room",this_object());
}

void
reset_room2()
{
   gateguard2 = present("gateguard2");
   if(gateguard2 && gateguard2->query_name() != "andruil" && gateguard2->query_name() !="corpse")
      return;
   else
      gateguard2 = clone_object("/d/Rhovanion/common/npcs/elves/gateguard2");
   gateguard2 -> move_living("into a room",this_object());
}

init()
{
   ::init();
   add_action("do_read","read",0);
}

do_read(str)
{
   if (str != "sigh")
      return
   write(sign_long());
   return 1;
}

sign_long()
{
   return
   "On the sign you read: \n\n" +
   "    These caverns are part of King Thranduil's\n"
   + "    kingdom. Be carefull as he is known to be\n"
   + "    hard on those who offend or abuse his people.\n"
   + "\n        Please report any bugs/typos you find \n"
   + "        to Daneel, you can use bug/typo commands.\n\n";
}
