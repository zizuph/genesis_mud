#pragma strict_types
#pragma no_inherit
#pragma no_clone

inherit "/d/Kalad/room_std";

#include "defs.h"

private object commander, g1, g2, g3, k1, k2;

public void
create_room()
{
   set_short("A well-lit cave");
   set_long(
      "You have stumbled down into a large cave within the chasm wall. " +
      "The cave seems to have been recently carved out in a rather crude " +
      "fashion, but the walls are lined with bunks and covered with hanging " +
      "oil lamps. There is a large table in the middle of the cave with " +
      "several maps lying open on it. A small ladder leads up through the " +
      "chute you fell down.\n"
   );
   add_item(({"lamp", "oil lamp", "lamps", "oil lamps"}),
      "Solid iron lamps firmly attached to the cave walls.\n");
   add_item(({"bunk", "bunks"}), "The bunks have been used recently.\n");
   add_item(({"table", "large table"}), "The table is covered with maps.\n");
   add_item(({"map", "maps"}), "They are maps of the area north of Kabal.\n");
   add_item(({"ladder", "small ladder"}), "The ladder leads up the chute.\n");
   add_item("chute", "The chute leads down from the ledge into the cave.\n");
   add_exit(ROOM+"ledge", "up", 0, 3);
   reset_room();
}

public void
reset_room()
{
   if(!commander)
   {
      commander = clone_object(RAID + "npc/cave_knight");
      commander->arm_me();
   }

   if(!k1)
   {
      k1 = clone_object(RAID + "npc/g_knight");
      k1->arm_me();
      commander->team_join(k1);
   }

   if(!k2)
   {
      k2 = clone_object(RAID + "npc/g_knight");
      k2->arm_me();
      commander->team_join(k2);
   }

   if(!g1)
   {
      g1 = clone_object(RAID + "npc/guard");
      g1->arm_me();
      commander->team_join(g1);
   }

   if(!g2)
   {
      g2 = clone_object(RAID + "npc/guard");
      g2->arm_me();
      commander->team_join(g2);
   }

   if(!g3)
   {
      g3 = clone_object(RAID + "npc/guard");
      g3->arm_me();
      commander->team_join(g3);
   }

   commander->move(this_object(), 1);
   k1->move(this_object(), 1);
   k2->move(this_object(), 1);
   g1->move(this_object(), 1);
   g2->move(this_object(), 1);
   g3->move(this_object(), 1);
}
