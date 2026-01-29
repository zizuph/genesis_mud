inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("An intersection within the drow city of Undraeth");
   set_long("Immense structures of rock known as stalagmites and stalactites "+
      "tower above you, having been shaped by the powerful magics of the "+
      "city's population into inhabitable buildings. "+
      "The air here is slightly warm and stagnant, the former due to the "+
      "large number of living beings nearby, and the latter to the city's "+
      "subterranean location. "+
      "An intersection of streets is before you, one heading to the west, "+
      "one to the north, another to the east, a fourth to the south and "+
      "finally to the southwest.\n");
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
   add_exit(CPASS(drow/d36),"west");
   add_exit(CPASS(drow/d39),"north");
   add_exit(CPASS(drow/d45),"east","@@block");
   add_exit(CPASS(drow/d41),"south","@@block");
   add_exit(CPASS(drow/monument),"southwest","@@msg");
   set_noshow_obvious(1);
}
block()
{
   write("You suddenly are overcome by a tremendous urge to sleep...\n");
   say(QCTNAME(TP) + " suddenly looks very drowsy, then slowly lies "+
      "down to take a nap.\n");
   TP->command("snore");
   return 1;
}
msg()
{
   write("A towering monument of a drow female looms over you.\n");
   write("It is visible well before you get anywhere near it.\n");
   return 0;
}
