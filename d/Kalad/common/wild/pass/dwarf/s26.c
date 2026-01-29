inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;
object ob2;
object ob3;
object ob4;
object ob5;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("From here you can see the edges of a large ruin "+
      "westwards, while the littered road continues "+
      "north and south. To the east another ruin "+
      "lingers on the edge of your lightsource, but looks "+
      "so destroyed that you doubt you can enter it.\n");

   add_item(({"littered","refuse","rubble"}),
      "It is all over this once proud road.\n");
   add_item(({"building","temple","block","blocks","stone blocks","roof","walls"}),
      "Most of the southwestern ruin has decayed into a rubble of broken stones, "+
      "but some of the walls still stand tall and seems to even hold up "+
      "a roof.\n");
   add_item("road","The road was once skillfully constructed by "+
      "using large, flat stones that was put edge to edge in "+
      "marvellous patterns. But now its all cracked and ruined. "+
      "Several stones lacks and the ones still here have suffered "+
      "from long time of decay.\n");

   add_exit(CPASS(dwarf/s27),"south");
   add_exit(CPASS(dwarf/s23),"north");

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob1->arm_me();
      ob1->move_living("M",TO);
   }
   if(!objectp(ob2))
      {
      ob2=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob2->arm_me();
      ob2->move_living("M",TO);
   }
   if(!objectp(ob3))
      {
      ob3=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob3->arm_me();
      ob3->move_living("M",TO);
   }
   if(!objectp(ob4))
      {
      ob4=clone_object(CPASS(dwarf/npc/dwarf_guard));
      ob4->arm_me();
      ob4->move_living("M",TO);
   }
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   tell_room(TO,"Some dwarves arrive along the path.\n");
}
