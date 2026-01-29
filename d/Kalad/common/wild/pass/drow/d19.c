inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("Immense structures of rock known as stalagmites and stalactites "+
      "tower above you, having been shaped by the powerful magics of the "+
      "city's population into inhabitable buildings. "+
      "The air here is slightly warm and stagnant, the former due to the "+
      "large number of living beings nearby, and the latter to the city's "+
      "subterranean location. "+
      "The sheer face of a cavern wall rises in the north, its top lying in "+
      "darkness. "+
      "The street you are journeying along continues to the east and west.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_exit(CPASS(drow/d15),"west");
   add_exit(CPASS(drow/d27),"east");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/rand_drow));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A citizen of this city suddenly appears before you.\n");
   }
}
