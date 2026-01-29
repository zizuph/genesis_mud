inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

create_room() 
{
 street = "overgrown, stone paved road";
 where = "southeast";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "tufts of light green grass";
 extraline = "You are on a grassy plateau extending as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " cover the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast.";

  add_exit(DUN_DIR+"road/r06","northwest",0);
  add_exit(DUN_DIR+"road/r04","southeast",0);

  make_the_room();
}

query_road()
{
 return 1;
}

