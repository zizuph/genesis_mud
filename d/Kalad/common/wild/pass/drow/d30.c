inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("A veritable kaleidoscope of stalagmites and stalactites "+
      "surround you, filling your field of view. These immense structures of "+
      "rock rise far above the ground, having been magically enhanced by the "+
      "native population into the astounding structures before you now. "+
      "The air around you is warm from the presence of numerous living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "The sheer face of a cavern wall rises in the north, its top lying in "+
      "darkness. "+
      "To the south lies a chasm of immense proportions. "+
      "The street you are on curves sharply here, heading off to the "+
      "northwest and northeast.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item("chasm",
      "A great, yawning maw within the surface of this cavern, its seemingly bottomless "+
      "appearance leads you to think twice before heading in that direction.\n");
   add_exit(CPASS(drow/d27),"northwest");
   add_exit(CPASS(drow/d35),"northeast","@@msg");
   add_exit(CPASS(drow/chasm/c1),"south","@@block");
   set_noshow_obvious(1);
}
msg()
{
   write("It seems strangely quiet in this section of Undraeth...\n");
   return 0;
}
block()
{
   write("That would be foolish, for it would lead to your "+
      "instant death.\n");
   return 1;
}
