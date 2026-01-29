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
   set_long("A myriad number and variety of stalagmites and stalactites "+
      "encompass your field "+
      "of view. These immense structures of rock rise far above you, having "+
      "been structurally enhanced by the populace of the city into the "+
      "strangely beautiful structures before you. "+
      "The air around you is warm from the presence of so many living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "The sheer face of a cavern wall rises in the northwest, its top lying in "+
      "darkness. "+
      "A large stalagmite compound lies to the south. "+
      "The street gently arcs here, curving to the east and southwest.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"large stalagmite compound","large compound","stalagmite compound","compound"}),
      "A dense cluster of stalagmites that have been magically twisted and "+
      "formed into a structure reminiscent of surface citadels and castles.\n");
   add_exit(CPASS(drow/d19),"east");
   add_exit(CPASS(drow/house7/entrance),"south");
   add_exit(CPASS(drow/d8),"southwest");
   set_noshow_obvious(1);
}
block()
{
   write("You attempt to go south but are almost immediately met by an "+
      "invisible barrier with the consistency of molasses. The more effort you "+
      "place into going south, the slower you move, until in a very short "+
      "time you are completely motionless.\n");
   say(QCTNAME(TP) + " begins to head south but soon slows " + TP->query_possessive() + " walking "+
      "until in a very short time, " + TP->query_pronoun() + " has stopped "+
      "completely.\n");
   return 1;
}
