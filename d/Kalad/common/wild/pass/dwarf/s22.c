inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You seem to be at the western side of a small "+
      "plaza situated inbetween several buildings that has "+
      "survived the destiny of destruction and pillaging. "+
      "From here you can walk both to the northeast and southeast, "+
      "making a turn around "+
      "a monument in the center of this old plaza. Another road leads "+
      "to the west into a large stone-building, from where you notice the smell "+
      "of leather drifting towards you, and the sounds of metal "+
      "almost drowning the rumbling voices of several dwarves.\n");
   add_item(({"buildings","bilding"}),
      "The buildings looks to be in a good shape, and you can see "+
      "some dwarves working in the read, weak light pouring out of "+
      "the door of the eastern one.\n");
   add_item("plaza","The plaza seems to be surrounded by some buildings, "+
      "that dwarves walks in and out of. In the center you see a large "+
      "monument.\n");
   add_item(({"path","street","streets"}),"Among some rubble you can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"monument","statue"}),
      "The monument is of a broad dwarf sitting on a horse.\n");
   add_exit(CPASS(dwarf/shop/m1),"west");
   add_exit(CPASS(dwarf/s19),"northeast");
   add_exit(CPASS(dwarf/s21),"southeast");
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
      tell_room(TO,"A dwarf comes wandering out of the western "+
         "building.\n");
   }
}
