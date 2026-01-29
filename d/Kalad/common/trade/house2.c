inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Milashk, modified by Antharanos */
   create_room()
{
   set_short("An old house");
   set_long("This house looks abandoned, but you can tell its not because "
      +"of the lack of dust on the floor. The house is in a bad "
      +"shape as the walls, floor and ceiling are cracked and faded due "
      +"to extreme age. Numerous fist-sized holes riddle the floor.\n");
   add_item(({"floor","walls","wall","ceiling"}),
      "The wooden structures all bear the ravages of time and improper "+
      "care, for they look near collapse.\n");
   add_item(({"fist-sized holes","holes","hole"}),
      "It looks as if they were chewed out by small, sharp teeth.\n");
   add_exit(TRADE(cliff_connect2),"east");
   hear_bell = 1;
   INSIDE;
   add_prop(ROOM_NO_TIME_DESC,1);
   set_alarm(2.0,0.0,"msg");
}
msg()
{
   tell_room(TO,"Nearly a dozen rats scurry away upon your entrance "+
      "into the house and disappear into the holes in the floor.\n");
   return 1;
}
