inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The Sheik's abode");
   set_long("This room is truly a place fit for a Sheik.\n"+
      "The interior of this chamber has been fashioned of the finest silks, "+
      "their glossy surfaces making the room sparkle before your eyes. A "+
      "great redwood table, a true rarity in the desert, adorns the center "+
      "of the room, while at the far end lies a large mass of silk pillows. "+
      "A pair of steel lanterns hang from their wooden stands, basking "+
      "the room with their gentle glow. A steel pot is off to one side, a "+
      "wonderful scent emerging from it. A plush red carpet completely "+
      "covers the floor.\n");
   add_item(({"room","chamber"}),"Its where you currently are.\n");
   add_item(({"interior","finest silks","finest silk","silks","silk","glossy surfaces","glossy surface","surfaces","surface"}),
      "The sides and ceiling of this chamber are "+
      "fashioned of pure white silk, a true commodity here in the waste, "+
      "for not only does it provide protection from the heat but it also "+
      "brings enjoyment to the eye.\n");
   add_item(({"great redwood table","great table","redwood table","table"}),
      "A magnificently crafted table upon which the Sheik eats his meals.\n");
   add_item(({"large mass of silk pillows","large mass","mass","silk pillows","silk pillow","pillows","pillow"}),
      "An incredibly soft-looking spot where the great Sheik sits and also "+
      "sleeps upon.\n");
   add_item(({"pair","steel lanterns","steel lantern","lanterns","lantern"}),
      "They provide a steady illumination for this room.\n");
   add_item(({"wooden stands","wooden stand","stands","stand"}),"The "+
      "two lanterns are hanging from them.\n");
   add_item(({"steel pot","pot"}),"A wonderful aroma of some sort wafts "+
      "from this brand new cooking pot.\n");
   add_item(({"plush red carpet","plush carpet","red carpet","carpet"}),
      "An elegant carpet also made from silk. A large image of a blood-red sun "+
      "has been sewn into the delicate fiber of the carpet.\n");
   add_item(({"floor"}),"Its been completely covered by the carpet.\n");
   add_exit(CPASS(desert/camp/c20),"northwest",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/bed_shk");
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"The Sheik of the Iriphawa tribe of the Bedellin emerges into view.\n");
   }
}
