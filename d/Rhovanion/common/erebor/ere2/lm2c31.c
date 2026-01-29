inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{
  object door;

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(6);
  set_long("This is the center of the park. Here you can see a fountain "
        + "and some benches, perfect for loving couples. When you "
        + "study this place a little closer, you realise that the "
        + "architect have made it look like a clearing of sort. The "
        + "exits are almost hidden from here, and you feel completely "
        + "safe from anyone trying to spy on you.\n");

  add_item("fountain","The fountain is made to look like "
        + "a fish. From the mouth is water pouring down into "
        + "a pool at the base of the construction. If you "
        + "listen carefully, you can hear water running through "
        + "invisible tunnels below the park, so there is no "
        + "chance the pool will overflow.\n");
 
  add_item("bench","The benches look quite comfortable from here. "
        + "Still, can a bench made from pure rock ever be "
        + "comfortable?\n");
 
  add_exit(CAVE_DIR + "lm2c16","north",0,1);
  add_exit(CAVE_DIR + "lm2c44","south",0,1);
}
