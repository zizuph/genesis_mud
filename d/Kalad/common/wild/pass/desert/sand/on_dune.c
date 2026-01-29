inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On top of a sand dune");
   set_long("You are at the very top of the long ridge of a sand dune. "+
      "The great mass of sand stretches to the north and south, looking "+
      "exactly like the sinuous body of a desert snake. A hot wind rushes "+
      "at you from the east. Several features catch your eye here at this "+
      "high vantage point. A long, thin road lies in the distant north, and "+
      "just east from here past smaller dunes is a rolling grassland. To the "+
      "southeast lies what appears to be a small settlement or camp of some "+
      "sort. By far the most interest to you, however, is the jutting, "+
      "blackened remains of a tower that rises from the sand before you.\n");
   add_item(({"top","sand dune","dune","long ridge","ridge"}),"A large "+
      "pile of sand that has been formed by the continual actions of the "+
      "desert wind, which blows steadily from the east. It appears as "+
      "if you could climb down the west side of the dune.\n");
   add_item(({"long thin road","long road","thin road","road"}),"The "+
      "thin grey line in the distance can only be the Caravan Route, the "+
      "sole roadway leading through the Great Kalad Waste.\n");
   add_item(({"rolling grassland","grassland"}),"It is the only green "+
      "area in the desert you can see from here.\n");
   add_item(({"small settlement","settlement","camp"}),"A series of tents "+
      "roughly gathered into a circle. Smoke can be seen rising from several "+
      "of them.\n");
   add_item(({"jutting blackened remains","tower","jutting remains","blackened remains","remains"}),
      "A twisted black shape that resembles a gnarled finger rising into "+
      "the sky.\n");
   add_item(({"sand"}),"It lies everywhere and seems to cover everything.\n");
   add_item(({"smoke"}),"Thin columns in the distance.\n");
   add_cmd_item("down","climb","@@climb");
   add_exit(CPASS(desert/sand/r5),"down","@@msg");
}
msg()
{
   write("You enter the ruined tower.\n");
   return 0;
}
climb()
{
   write("You climb down the dune.\n");
   TP->move_living("down the side of the dune","/d/Kalad/common/wild/pass/desert/sand/d27");
   return "You made it safely down the side of the dune.\n";
}
