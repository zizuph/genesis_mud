inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("East you see a large ruin that once "+
      "might have been some kind of temple. It is hard to "+
      "be sure since only the eastern part of it has any roof "+
      "at all. Time has surely done its work in this neighborhood. "+
      "This littered road continues further "+
      "on towards a corner southwards and a crossroad in the north.\n");

   add_item(({"littered","refuse","rubble"}),
      "It is all over this once proud road.\n");
   add_item(({"building","temple","block","blocks","stone blocks","roof","walls"}),
      "Most of the building has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof further east.\n");
   add_item("road","The road was once skillfully constructed by "+
      "using large, flat stones that was put edge to edge in "+
      "marvellous patterns. But now its all cracked and ruined. "+
      "Several stones lacks and the ones still here have suffered "+
      "from long time of decay.\n");

   add_exit(CPASS(dwarf/s1),"south");
   add_exit(CPASS(dwarf/s3),"north");

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
   {
      ob1 = clone_object(CPASS(dwarf/npc/duergar));
      ob1 -> arm_me();
      ob1 -> set_random_move(10);
      ob1->move_living("M",TO);
      tell_room(TO,"A duergar comes rambling along the street.\n");
   }
}
