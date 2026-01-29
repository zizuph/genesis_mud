inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The quarters of the priestesses");
   set_long("Judging from the opulence of this chamber, it would be a "+
      "fair guess that this is the private residence of the priestesses of "+
      "House Kilsek, for such opulence would never be bestowed unto a mere "+
      "male. A myriad number of decorations, wrought in faerie fire, cover "+
      "the walls and ceiling, while the floor is blanketed by a rug of pure, "+
      "black spider silk. A pair of beds along with two platinum chests "+
      "occupy the room, while a small shrine to Lolth, lies between them.\n");
   add_item(({"chamber","room"}),
      "It is where you presently are, have a look around.\n");
   add_item(({"decorations","decoration","faerie fire","fire"}),
      "Intricate images depicting drow worshipping and prostating themselves "+
      "before the magnificence that is Lolth, the Spider Queen.\n");
   add_item(({"walls","wall","ceiling"}),
      "Made from night-black stone, they are blanketed with faerie fire images.\n");
   add_item(({"floor","ground"}),
      "It is obscured by the rug that lies there.\n");
   add_item(({"rug","black spider silk","black silk","spider silk","silk"}),
      "An extremely delicate-looking rug that carpets the floor, despite its "+
      "appearance, it is quite sturdy.\n");
   add_item(({"pair of beds","beds","bed"}),
      "Extremely comfortable-looking places to sleep.\n");
   add_item(({"platinum chests","chests","platinum chest","chest"}),
      "A chest, roughly three feet in length made from solid platinum.\n");
   add_item(({"small shrine","shrine"}),
      "A private place to worship, and make sacrifices to, Lolth.\n");
   add_exit(CPASS(drow/house5/main_hall),"south",0,-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   recently_searched = 0;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h5_priest2));
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
}
void
init()
{
   ::init();
   AA(search_chests,search);
}
int
search_chests(string str)
{
   if(!str || str != "chests")
      return 0;
   if(recently_searched)
      {
      write("You discover nothing of worth within the chests.\n");
      return 1;
   }
   recently_searched = 1;
   write("You start to search the chests.\n");
   say(QCTNAME(TP) + " starts to search the chests.\n");
   set_alarm(6.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   write("After a thorough search, you discover a diamond and a gem within "+
      "one of the chests!\n");
   write("You quickly grab them up.\n");
   say(QCTNAME(TP) + " takes something from one of the chests.\n");
   clone_object(CPASS(obj/diamond))->move(TP);
   clone_object(CPASS(obj/srgem))->move(TP);
   return;
}
