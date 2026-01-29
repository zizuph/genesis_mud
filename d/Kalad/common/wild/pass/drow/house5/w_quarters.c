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
   add_prop(ROOM_I_LIGHT,0);
   set_short("The quarters of the warriors");
   set_long("This rectangular-shaped chamber must be the residence of the "+
      "warriors of House Kilsek, for upon the walls are placed numerous "+
      "weapons and armour, all within easy reach of a drow warrior. Narrow "+
      "beds line the southern side of the chamber while several chests lie "+
      "on the western and eastern sides. Otherwise, this room is bare of "+
      "the faerie fire decorations so common throughout the rest of the "+
      "compound.\n");
   add_item(({"quarters","residence","rectangular-shaped chamber","chamber"}),
      "It is where you are now, look around.\n");
   add_item(({"walls","wall","floor","ceiling","ground"}),
      "The room appears to have been constructed from the same dark stone "+
      "commonly found throughout the Dark Dominion and this drow city.\n");
   add_item(({"numerous weapons","numerous armour"}),
      "A variety of swords, spears, polearms, daggers, knives and axes line "+
      "the side walls. In addition, several types of chainmail and even "+
      "platemail hang aside the assortment of weapons.\n");
   add_item(({"narrow beds","narrow bed","beds","bed"}),
      "Each of the beds looks barely large enough to accomodate a drow "+
      "warrior, no doubt their comfort is not a concern here.\n");
   add_item(({"chests","chest"}),
      "Stout wooden chests used as a place of storage for the belongings of "+
      "the drow who reside in this room.\n");
   add_exit(CPASS(drow/house5/main_hall),"north",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h5_patron));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(drow/npc/h5_firstboy));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"A few drow emerge from the darkness.\n");
   }
}
