inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
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
      "A stalagmite compound lies to the west, while another one is to the "+
      "east. "+
      "The street curves here, heading to the northeast and south.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"stalagmite compound","compound"}),
      "Which compound? The western one or the eastern one?\n");
   add_item(({"western compound"}),
      "A decent-sized collection of stalagmites grouped to form a building. "+
      "A glowing plaque hangs before it.\n");
   add_item(({"eastern compound"}),
      "A large collection of stalagmites huddled together to form a "+
      "building of solid rock. A glowing sign hangs before it.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit(CPASS(drow/shop/bank),"west","@@msg1",-1,-1);
   add_exit(CPASS(drow/d27),"northeast");
   add_exit(CPASS(drow/shop/shop),"east","@@msg2",-1,-1);
   add_exit(CPASS(drow/d21),"south");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
msg1()
{
   write("You stride into the western compound.\n");
   say(QCTNAME(TP) + " strides into the western compound.\n");
   return 0;
}
msg2()
{
   write("You walk into the eastern compound.\n");
   say(QCTNAME(TP) + " walks into the eastern compound.\n");
   return 0;
}
plaque()
{
   return "\n"+
   "Written in glowing purple letters is the following:\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
   "* Belaern del Undraeth............................*\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
sign()
{
   return "\n"+
   "Written in glowing green letters is the following:\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
   "* Yath del Undraeth..............................*\n"+
   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/rand_drow));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"Your attention is drawn to a shifting patch of "+
         "darkness.\n");
   }
}
