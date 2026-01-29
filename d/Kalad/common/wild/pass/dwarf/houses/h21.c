inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat - some houses */


void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("within a hallway, in Underhome");
   set_long("You walk along a hallway, cut into the rock. The walls "+
      "is plain, but wellcrafted some hundred years ago. On them "+
      "some torches hangs, lighting up the cavern. "+
      "A small cave lies to your southeast, and looks inhabitated. "+
      "The hallway continues northeastwards.\n");

   add_item("torches","They emit a weak light.\n");
   add_item(({"cave","house"}),
      "It is a small cave that propably is occupied "+
      "by a family or a single deep dwarf. A weak red light streams "+
      "out from the entrance.\n");
   add_item("walls","The walls are smooth to the touch, but fairly "+
      "uninterresting.\n");

   add_exit(CPASS(dwarf/houses/h22),"southeast");
   add_exit(CPASS(dwarf/houses/h23),"northeast");
   add_exit(CPASS(dwarf/s17),"southwest","@@walk@@");
}

walk()
{
   write("You leave the cavern and enter the trodden path.\n");
   return 0;
}
