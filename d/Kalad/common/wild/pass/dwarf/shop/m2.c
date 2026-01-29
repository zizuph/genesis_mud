inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Within a market-house in Underhome");
   set_long("You find yourself inside a large stone-building "+
      "that undoubtedly is a market-area where you and everyone "+
      "else can buy and sell almost anything. From the north you "+
      "notice that the smell of leather is strong, while "+
      "to the west you see a dark room with a sign "+
      "attached above the door.\n");
   add_item("sign","The sign is of a lump of gold, but also "+
      "with a word beneath it: 'Bank'.\n");
   add_exit(CPASS(dwarf/shop/bank),"west",0,-1,-1);
   add_exit(CPASS(dwarf/shop/m3),"north",0,-1,-1);
   add_exit(CPASS(dwarf/shop/m1),"south",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
}
reset_room()
{
   if(!objectp(ob1))
   {
      ob1=clone_object(CPASS(dwarf/npc/dwarf));
      ob1->arm_me();
      ob1->set_random_move(10);
      ob1->move_living("M",TO);
      tell_room(TO,"A dwarf comes walking happily from the north, "+
      "carrying a brand new backpack on his back.\n");
   }
}
