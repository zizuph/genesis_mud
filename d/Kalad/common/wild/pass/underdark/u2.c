inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Cave Entrance");
   set_long("You've reached a ledge near the summit of this mountain. "+
      "To the east lies a dark cave while far below you can see the valley "+
      "spread out to the southwest, filled with redwoods. Above you the rest "+
      "of the mountain lies.\n");
   add_item(({"ledge"}),"A flat space here on the side of the mountain.\n");
   add_item(({"summit","mountain"}),"Even though you have climbed a great "+
      "deal of distance, the bulk of the mountain lies far above you, with "+
      "its towering peak covered in snow.\n");
   add_item(({"snow"}),"The glare from the intense Kaladian sun nearly blinds "+
      "you when you glance at the snow.\n");
   add_item(({"dark cave","cave"}),"The darkness seems inpenetrable.\n");
   add_item(({"valley","redwoods"}),"A beautiful panorama that spreads out far "+
      "below you. The sight is truly something that you shall hold dear to "+
      "you for the rest of your life.\n");
   add_exit("/d/Kalad/common/wild/pass/underdark/u1", "down",0,2);
   add_exit("/d/Kalad/common/wild/pass/underdark/u3", "east",0,-1,0);
}
void
init()
{
   ::init();
   write("A rush of cold mountain air greets you.\n");
   say("A rush of cold mountain air greets " + QTNAME(TP) + ".\n");
}
