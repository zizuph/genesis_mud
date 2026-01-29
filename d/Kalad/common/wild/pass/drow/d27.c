inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("Countless stalagmites and stalactites fill your vision for "+
      "as far as you can see. These immense structures of rock rise far "+
      "above you, having been magically altered by the city's inhabitants into "+
      "the fantastic buildings that they are now. "+
      "The air here is warm, no doubt due to the presence of so many living "+
      "beings in one area. Despite its warmth, it is stale and stagnant, "+
      "typical of an underground environment. "+
      "The sheer face of a cavern wall rises in the north, broken only by a large "+
      "series of steps carved into it. "+
      "Just to the south lies a stalagmite compound. "+
      "You are presently at an intersection, with streets travelling to the "+
      "west, southwest and southeast.\n");
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
   add_item(({"large series of steps","steps"}),
      "A great stairway that lies in the north. It leads into the cavern "+
      "wall itself, where it is lost in darkness.\n");
   add_item(({"stalagmite compound","compound"}),
      "A group of stalagmites clustered together to form a building. "+
      "A large glowing sign hangs in front of the building.\n");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit(CPASS(drow/d19),"west");
   add_exit(CPASS(drow/guild/entrance),"north");
   add_exit(CPASS(drow/d30),"southeast");
   add_exit(CPASS(drow/shop/adv_guild),"south","@@msg",-1,-1);
   add_exit(CPASS(drow/d20),"southwest");
   set_noshow_obvious(1);
}
block()
{
   write("You try to continue deeper into the city but are soon stopped "+
      "by a large patrol of drow and turned back.\n");
   say(QCTNAME(TP) + " tries to continue deeper into the city but is "+
      "soon stopped by a large patrol of drow and turned back.\n");
   return 1;
}
msg()
{
   write("You step out of the street and into the stalagmite compound.\n");
   say(QCTNAME(TP) + " steps out of the street and into the stalagmite "+
      "compound in the south.\n");
   return 0;
}
sign()
{
   return "\n"+
   "Written in glowing yellow letters is the following:\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
   "~ Sargtlin yath del Undraeth......................~\n"+
   "~ Jal z'ress ulu Lolth!...........................~\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
