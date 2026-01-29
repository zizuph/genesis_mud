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
   set_long("Gigantic structures of rock known as stalagmites and "+
      "stalactites tower far above you, having been magically altered by "+
      "the native population into the impressive structures before you now. "+
      "The air here is warm, yet is quite stagnant and oppressive. It is "+
      "almost uncanny in its immobility, for the air here is as dead as can "+
      "be. "+
      "The sheer face of a cavern wall rises in the north, its top lying "+
      "in darkness. Visible in the south, just past a small stalagmite "+
      "compound is an immense chasm. "+
      "The street curves slightly here, running along the cavern wall to "+
      "the southwest and east.\n");
   add_item(({"gigantic structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"small stalagmite compound","small compound","stalagmite compound","compound"}),
      "A small cluster of stalagmites that have been fused together to "+
      "form a building.\n");
   add_item(({"immense chasm","chasm"}),
      "A gigantic rent within the surface of this chasm, even from this "+
      "removed distance, it appears large enough to swallow a small mountain.\n");
   add_exit(CPASS(drow/d35),"southwest");
   add_exit(CPASS(drow/d43),"east");
   add_exit(CPASS(drow/guild1/entrance),"south","@@block");
   set_noshow_obvious(1);
}
block()
{
   write("A strange force seems to prevent you from heading in that direction.\n");
   say("A strange force seems to prevent " + QTNAME(TP) + " from heading "+
      "south.\n");
   return 1;
}
msg()
{
   write("You slowly stride into the compound to the south.\n");
   say(QCTNAME(TP) + " slowly strides into the compound in the south.\n");
   return 0;
}
