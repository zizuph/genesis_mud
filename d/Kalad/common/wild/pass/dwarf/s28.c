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
   set_long("From here you can see the corner of a large ruin "+
      "northwestwards, while the littered road continues "+
      "northeast and west. To the northeast you think you can "+
      "see the road end up in a crossroad.\n");
   
   add_item(({"littered","refuse","rubble"}),
      "It is all over this once proud road.\n");
   add_item(({"building","temple","block","blocks","stone blocks","roof","walls"}),
      "Most of the northwestern ruin has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof. There is a large crack in the wall to the northwest.\n");
   add_item("road","The road was once skillfully constructed by "+
      "using large, flat stones that was put edge to edge in "+
      "marvellous patterns. But now its all cracked and ruined. "+
      "Several stones lacks and the ones still here have suffered "+
      "from long time of decay.\n");
   
   add_exit(CPASS(dwarf/s29),"west");
   add_exit(CPASS(dwarf/s27),"northeast");
   add_exit(CPASS(dwarf/duergar/d10),"northwest");
   
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
reset_room()
{
   if(!objectp(ob1))
   {
      ob1=clone_object(CPASS(dwarf/npc/dwarf));
      ob1->arm_me();
      ob1->set_random_move(10);
      ob1->move_living("M",TO);
      tell_room(TO,"A dwarf comes wandering out of the darkness.\n");
   }
}

