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
   set_long("A great many stalagmites and stalactites fill your field "+
      "of view. These immense structures of rock rise far above you, having "+
      "been structurally enhanced by the populace of the city into the "+
      "strangely beautiful structures before you. "+
      "The air around you is warm from the presence of so many living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "The sheer face of a cavern wall rises in the northwest, its periphery lost in "+
      "darkness. "+
      "The street curves gently here, travelling in an arc to the northeast "+
      "and to the south.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_exit(CPASS(drow/d15),"northeast");
   add_exit(CPASS(drow/d9),"south");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/b_w_spider));
      ob1 -> move_living("M",TO);
      tell_room(TO,"Something moves in the nearby darkness.\n");
   }
}
