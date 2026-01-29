inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Entrance to the drow city of Undraeth");
   set_long("Immense structures of rock known as stalagmites and stalactites "+
      "tower above you, having been shaped by the powerful magics of the "+
      "city's population into inhabitable buildings. "+
      "The air here is slightly warm and stagnant, the former due to the "+
      "large number of living beings nearby, and the latter to the city's "+
      "subterranean location. "+
      "The sheer face of a cavern wall rises in the west, its top lying in "+
      "darkness. "+
      "An intersection of streets is before you, one heading to the northeast, "+
      "the other to the southeast, and the larger one directly east.\n"+
      "A large glowing sign stands here.\n");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
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
   add_exit(CPASS(drow/d4),"west");
   add_exit(CPASS(drow/d10),"northeast");
   add_exit(CPASS(drow/d11),"east");
   add_exit(CPASS(drow/d12),"southeast","@@block");
   set_noshow_obvious(1);
}
sign()
{
   return "\n"+
   "Written in glowing purple letters are the following words:\n"+
   "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"+
   "| Dos phuul wund lil ust usstil del lil drow............ |\n"+
   "| Dos phuul wun Undraeth! Orthae usstil del Lolth.       |\n"+
   "| Noamuth, khaless naur uss.                             |\n"+
   "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
block()
{
   write("You begin to venture forth further into the city, but are "+
      "soon stopped by a large contingent of drow warriors, accompanied by a drow "+
      "wizard. They command you to leave, and considering that there are "+
      "well over two dozen warriors, not to mention the wizard, you hastily "+
      "retreat.\n");
   say(QCTNAME(TP) + " begins to venture forth further into the city, "+
      "but is soon stopped by a large contingent of drow warriors, "+
      "accompanied by a drow wizard. The drow say something to " + QTNAME(TP) + " and " + TP->query_pronoun() + " hastily retreats in your direction.\n");
   return 1;
}
