inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the Bedellin camp");
   set_long("You are standing within the Bedellin nomads' camp. The "+
      "one constant of the desert waste, the swirling sand, is much less "+
      "obvious here, due to the protecting embrace of the nomad tents "+
      "which blocks off the fierce desert wind from stirring up the sand. "+
      "Rising in the center of the camp in the east is a giant tent. "+
      "The desert sky above is clear, leaving the land unprotected from "+
      "the scorching rays of the harsh Kaladian sun.\n");
   add_item(({"bedellin camp","camp"}),"It surrounds you from all sides.\n");
   add_item(({"ever-present swirling sand","ever-present sand","swirling sand","sand"}),
      "The light brown sand lies scattered around the camp.\n");
   add_item(({"sand-colored tents","tents","tent"}),"The dwellings used "+
      "most commonly by the nomadic Bedellin, perfect for a people "+
      "constantly on the move.\n");
   add_item(({"clear desert sky","clear sky","desert sky","sky"}),
      "The astoundingly blue sky is clear of clouds, more evidence of the "+
      "dry nature of this place.\n");
   add_item(({"kaladian sun","sun"}),"A harsh yellow orb that bakes "+
      "this land to a scorching temperature.\n");
   add_item(({"land"}),"The desert landscape of the Great Kalad Waste.\n");
   add_item(({"giant tent"}),"A large canvas tent that occupies the "+
      "center of the Bedellin camp. There looks to be a slit in the side "+
      "of the giant tent.\n");
   add_item(({"slit","side"}),"A hole in the tent, possible one large "+
      "enough to accomodate you.\n");
   add_item(({"hole"}),"It looks just large enough for you to enter.\n");
   add_cmd_item(({"east","hole"}),"enter","@@enter");
   add_cmd_item("hole","enter","@@enter");
   add_exit(CPASS(desert/camp/c23),"west",0,2);
   add_exit(CPASS(desert/camp/c21),"north",0,2);
}
enter()
{
   write("You crawl into the hole in the side of the tent.\n");
   set_dircmd("hole");
   TP->move_living("into the tent","/d/Kalad/common/wild/pass/desert/camp/c25");
   return "You've crawled out of the hole, and find yourself inside the "+
   "tent of the Sheik.\n";
}
