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
   set_long("Immense structures of rock known as stalagmites and stalactites "+
      "tower above you, having been shaped by the powerful magics of the "+
      "city's population into inhabitable buildings. "+
      "The air here is slightly warm and stagnant, the former due to the "+
      "large number of living beings nearby, and the latter to the city's "+
      "subterranean location. "+
      "The sheer face of a cavern wall rises in the west, its top lying in "+
      "darkness. "+
      "An intersection of streets is before you, one heading to the northeast, "+
      "the other to the southeast, and the larger one directly east.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"intersection"}),"Its where you are right now.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
}
