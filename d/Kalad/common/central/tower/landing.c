inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Where the unfortunates land when they fall from the top of the 
bell tower. It is just west of the Citadel and east of Market St */
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 3;
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Among the bushes");
   set_long("You find yourself in a small open field, whose fringes are "+
      "surrounded by thorny bushes. To the east is the towering bulk of "+
      "the High Lord's Citadel. A small path leads west, out of this "+
      "clearing and back onto the road.\n");
   add_item(({"small open field","small field","open field","field","clearing"}),
      "A small place where some grass is growing. There is a strange reddish "+
      "tinge to the ground.\n");
   add_item(({"ground"}),"The grass-covered soil seems to be have been "+
      "soaked by human blood!\n");
   add_item(({"thorny bushes","bushes","bush"}),"The nasty-looking plants "+
      "ring this small clearing, making it impossible to go anywhere but "+
      "to the west.\n");
   add_item(({"high lord's citadel","citadel"}),"A grand structure of "+
      "finest stone, the residence of the High Lord of Kabal.\n");
   add_item(({"small path","path"}),"A narrow dirt lane.\n");
   add_exit(CENTRAL(market/s3),"west","@@go_south");
}

go_south()
{
   write("The path soon seems to dwindle in more of an "+
      "southwestern direction. Soon you find yourself "+
      "on the Market street.\n\n");
   return 0;
}
