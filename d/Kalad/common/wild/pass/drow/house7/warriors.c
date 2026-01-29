inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The barracks of the warriors of House Claddath");
   set_long("The barracks of the warriors of House Claddath.\n"+
      "Numerous types of weapons and armours hang suspended from the "+
      "black walls of this room, with several mats lying on the floor. "+
      "A few chests lie on the north side of the room while small, "+
      "uncomfortable-looking beds line the southern wall.\n");
   add_item(({"barracks"}),
      "The location where the warriors of House Claddath live and train.\n");
   add_item(({"numerous weapons","weapons"}),
      "Every imaginable type of weapon is visible, all crafted from pure "+
      "adamantine.\n");
   add_item(({"numerous armours","armours"}),
      "Every imaginable type of armour is visible, all crafted from pure "+
      "adamantine.\n");
   add_item(({"black walls","walls","wall"}),
      "Constructed from the strangely dark rock of the Dark Dominion, it "+
      "seems to possess strange light-absorbing qualities.\n");
   add_item(({"mats","mat"}),
      "Hardened mats of leather used in training exercises.\n");
   add_item(({"floor"}),
      "It is constructed of a strange dark stone that appears to absorb "+
      "light...\n");
   add_item(({"chests","chest"}),
      "Platinum constructs that have been decorated with numerous runes "+
      "of archaic origins.\n");
   add_item(({"runes","rune"}),
      "They seem to twist and dance before your eyes.\n");
   add_item(({"small beds","uncomfortable-looking beds","beds","bed"}),
      "Tiny and utilitarian sleeping places.\n");
   add_exit(CPASS(drow/house7/main_hall),"down","@@msg",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h7_patron));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"Someone emerges from the darkness.\n");
   }
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
