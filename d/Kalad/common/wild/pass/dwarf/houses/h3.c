inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */


create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("within a hallway, in Underhome");
   set_long("You walk along a hallway, cut into the rock. The walls "+
      "is plain, but wellcrafted some hundred years ago. "+
      "A small cave lies to your west, and looks inhabitated. "+
      "To the north you see the entrance to something that looks "+
      "like a mine.\n");
   add_item("house","It is a small cave that propably is occupied "+
      "by a family or a single deep dwarf. A weak red light streams "+
      "out from the entrance.\n");
   add_item("walls","The walls are smooth to the touch, but fairly "+
      "uninterresting.\n");
   
   add_exit(CPASS(dwarf/houses/h4),"west",0,-1,-1);
   add_exit(CPASS(dwarf/mine/m14),"north",0,-1,-1);
   add_exit(CPASS(dwarf/houses/h2),"south",0,-1,-1);
   
}

