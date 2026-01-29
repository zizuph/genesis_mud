inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("Numerous stalagmites and stalactites encompass your field "+
      "of view. These immense structures of rock stretch far above the "+
      "ground, having been magically enchanted by the city's populace into "+
      "the incredible structures before you now. "+
      "Due to the many living beings dwelling within the city, the air is "+
      "comfortably warm, though it is somewhat oppressive and stagnant "+
      "because of the distance to the surface, where fresh air lies. "+
      "Stalagmite compounds lie just off the road to the west and east. "+
      "The street you are on travels in a straight north-south manner.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"stalagmite compounds","compounds","stalagmite compound","compound"}),
      "Which compound? The western or eastern one?\n");
   add_item(({"western compound"}),
      "A large group of stalagmites that have been melded together to form an "+
      "impressive edifice of stone. A large glowing plaque hangs before "+
      "the building.\n");
   add_item(({"eastern compound"}),
      "A group of large stalagmites that have been meshed together to "+
      "form a building of sorts. Before it is a large glowing sign.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit(CPASS(drow/shop/blacksmith),"west","@@msg1",-1,-1);
   add_exit(CPASS(drow/d20),"north");
   add_exit(CPASS(drow/shop/pub),"east","@@msg2",-1,-1);
   add_exit(CPASS(drow/bazaar/b1),"south");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
msg1()
{
   write("You stride into the western compound and are greeted by a blast "+
      "of hellishly hot air.\n");
   say(QCTNAME(TP) + " heads in the direction of the western compound.\n");
   return 0;
}
msg2()
{
   write("You stride into the eastern compound and are greeted by the "+
      "noise of many people all crowded into one place.\n");
   say(QCTNAME(TP) + " heads towards the eastern compound.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/rand_drow));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(drow/npc/rand_drow));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      tell_room(TO,"Some figures come into view, having emerged from the "+
         "darkness itself.\n");
   }
}
plaque()
{
   return "The plaque reads:\n"+
   "The blacksmith of Undraeth\n";
}
sign()
{
   return "The sign reads:\n"+
   "The general shop of Undraeth\n";
}
