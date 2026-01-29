inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

create_room() 
{
 street = "decaying, stone paved road";
 where = "southeast";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "coarse dry green grass";
 extraline = "You are on a rolling plateau extending as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast.";

  add_exit(DUN_DIR+"road/r10","northwest",0);
  add_exit(DUN_DIR+"road/r08","southeast",0);

  make_the_room();
}

query_road()
{
 return 1;
}

reset_room()
{
}

