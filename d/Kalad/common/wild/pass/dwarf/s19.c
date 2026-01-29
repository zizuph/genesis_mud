inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat */
object ob1;
object ob2;
object ob3;
object ob4;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You seem to be at the northern side of a small "+
      "plaza situated inbetween several buildings that has "+
      "survived the destiny of destruction and pillaging. "+
      "From here you can walk both to the southeast and southwest, "+
      "making a turn around "+
      "a monument in the center of this old plaza. Another road leads "+
      "north alongside the eastern wall of a large building.\n");
   add_item(({"buildings","bilding"}),
      "The buildings looks to be in a good shape, and are probably "+
      "being in use by some of the deep dwarves that live in Underhome.\n");
   add_item("plaza","The plaza seems to be surrounded by some buildings, "+
      "that dwarves walks in and out of. In the center you see a large "+
      "monument.\n");
   add_item(({"path","street","streets"}),"Among some rubble you can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"monument","statue"}),
      "The monument is of a broad dwarf sitting on a horse.\n");
   add_exit(CPASS(dwarf/s18),"north");
   add_exit(CPASS(dwarf/s22),"southwest");
   add_exit(CPASS(dwarf/s20),"southeast");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/npc/dwarf));
      ob1->arm_me();
      ob1->move_living("M",TO);
   }
   if(!objectp(ob2))
      {
      ob2=clone_object(CPASS(dwarf/npc/dwarf));
      ob2->arm_me();
      ob2->move_living("M",TO);
   }
   if(!objectp(ob3))
      {
      ob3=clone_object(CPASS(dwarf/npc/dwarf));
      ob3->arm_me();
      ob3->move_living("M",TO);
   }
   if(!objectp(ob4))
      {
      ob4=clone_object(CPASS(dwarf/npc/dwarf));
      ob4->arm_me();
      ob4->move_living("M",TO);
   }
   ob1->set_stat(5,100);
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   tell_room(TO,"Some dwarves arrive out of the darkness.\n");
}
