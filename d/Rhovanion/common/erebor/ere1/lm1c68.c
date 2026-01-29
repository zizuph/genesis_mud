inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Immediately to your south you see a crossing of tunnels, this must "
         + "be the beginning of the Guard HeadQuarters. "
         + "From somewhere to the north you can hear the singing and laughter "
         + "of many people, maybe a tavern or pub is located further north. "
         + "The tunnel continues as far as you can see to the north, leading towards "
         + "a large hall.");

  add_exit(CAVE_DIR + "lm1c66","north",0,1);
  add_exit(CAVE_DIR + "lm1c69","south",0,1);
}
