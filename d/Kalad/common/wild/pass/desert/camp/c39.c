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
      "obvious here, due to the protecting embrace of the nomad tents, "+
      "which blocks off the fierce desert wind from stirring up the sand. "+
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
   add_exit(CPASS(desert/camp/c38),"west",0,2);
   add_exit(CPASS(desert/camp/c40),"east",0,2);
}
