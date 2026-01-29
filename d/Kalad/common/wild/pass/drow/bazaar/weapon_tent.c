inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Inside the weapon merchant's tent");
   set_long("You find yourself within the spacious interior of an "+
      "extremely large tent. Various weapons lie stacked in piles upon "+
      "the floor and hang from both the sides of the tent, as well as the "+
      "ceiling. Even with the great size of this place, there is just barely "+
      "enough room for yourself and the drow weapons that nearly "+
      "fill up this tent. A small corner of the tent appears to be clear "+
      "of any drow weapons, allowing some breathing room here.\n"+
      "The only 'exit' from here is the open flap behind you.\n");
   add_item(({"open flap","flap"}),
      "It is the only exit from this tent.\n");
   add_item(({"extremely large tent","large tent","tent"}),
      "Look around, you're inside it...\n");
   add_item(({"various weapons","piles","drow weapons"}),
      "A myriad assortment and variety of weapons fills this tent.\n");
   add_item(({"sides","side","ceiling"}),
      "The canvas material of the tent is barely visible due to the numerous "+
      "weapons everywhere.\n");
   add_item(({"small corner","corner"}),
      "A cleared space on the floor where no drow weapons lie.\n");
   add_item(({"floor"}),
      "It is barely visible due to the sheer volume of drow weapons lying "+
      "about.\n");
   add_exit(CPASS(drow/bazaar/b4),"exit",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/weapon_merchant));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"From behind a pile of drow weapons emerges a single figure.\n");
   }
}
