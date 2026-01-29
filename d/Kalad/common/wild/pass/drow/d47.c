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
      "The sheer face of a cavern wall rises to the north, its top lying in "+
      "perpetual darkness. "+
      "A stalagmite compound lies just to the east, off the street. "+
      "An intersection of streets is before you, one heading to the "+
      "northwest and southeast with another travelling to the northeast "+
      "and southwest.\n");
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
   add_item(({"stalagmite compound","compound"}),
      "A medium-sized cluster of stalagmites that have been magically "+
      "fused and molded with one another to form a building, one akin to castles "+
      "on the surface world.\n");
   add_exit(CPASS(drow/d43),"northwest","@@msg");
   add_exit(CPASS(drow/d50),"northeast","@@block");
   add_exit(CPASS(drow/house8/entrance),"east","@@msg1");
   add_exit(CPASS(drow/d51),"southeast","@@block");
   add_exit(CPASS(drow/d44),"southwest");
   set_noshow_obvious(1);
}
msg()
{
   write("The streets seem strangely abandoned here.\n");
   return 0;
}
msg1()
{
   write("You stride towards the compound in the east.\n");
   say(QCTNAME(TP) + " strides towards the compound just off the street.\n");
   return 0;
}
block()
{
   write("A radiant spider-web of light suddenly flashes into being "+
      "before you, blocking your way. It dissappears as soon as you back "+
      "away.\n");
   say("A radiant spider-web of light suddenly flashes into being "+
      "before " + QTNAME(TP) + ", blocking " + TP->query_possessive() + " way. "+
      "It dissappears as soon as " + TP->query_pronoun() + " backs away.\n");
   return 1;
}
