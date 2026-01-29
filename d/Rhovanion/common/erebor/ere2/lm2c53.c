inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("southern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("The buildings on both sides of the corridor differs quite "
        +  "a lot from eachother. One stinks of wealth and money, while "
        +  "the other one is more common in style.\n");
 
  add_exit(CAVE_DIR + "lm2c54","east","@@gem_shop");
  add_exit(CAVE_DIR + "lm2c52","west","@@mining_shop");
  add_exit(CAVE_DIR + "lm2c55","south",0,1);
  add_exit(CAVE_DIR + "lm2c50","north",0,1);
}
 
int
mining_shop()
{
write("The miningshop is closed. No way to break the door down.\n");
return 1;
}
 
int
gem_shop()
{
write("The gemshop is closed and locked. Maybe a good thief "
     + "could pick the lock, but you seriously doubt it.\n");
return 1;
}
