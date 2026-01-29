/*
ROOM: Hallway upstairs
BY: Korat
Date: Feb 14, 1995
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object ob1, ob2;

void
create_room()
{
   ::create_room();                         
   hear_bell = 2;                           
   
   set_short("The hallway upstairs in the City Council building");
   set_long(
      "This hallway leads towards a large, open bronze door in the "+
      "western end. A stairway decends downwards here, back to the offices of "+
      " the City council building. "+
      "The hall is very plain, no accessories are standing anywhere, and no "+
      "carpet covers the dirty wooden floor. "
   );
   set_time_desc(
      "Many people are walking up and down the corridor.\n",
      "It is unnaturally quiet around here.\n"
   );
   
   add_prop(ROOM_I_INSIDE, 1);
   
   
   add_item("offices",
      "There is an office to the west with a sign on the door.\n"
   );
   
   add_item(({"office", "sign"}),
      "The office to the west has a sign on the door reading 'Lord of "+
      "the City Council.'\n");
   
   add_exit(CENTRAL(plaza/cc_hall2),"down",0,-1,-1);
   add_exit(CENTRAL(plaza/cc_lord),"west",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      ob1 -> command("emote salutes you.");
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob2 -> command("emote yawns.");
      ob1 -> team_join(ob2);
   }
}
