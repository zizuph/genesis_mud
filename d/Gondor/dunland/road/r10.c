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
 vegetation = "coarse dry yellow-green grass";
 extraline = "You are on a grassy plateau extending as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " covers the land of " +county+ ". You see a very old"
           + " road running in from the northwest and vanishing to the"
           + " southeast. There is a distant line of trees to the north.";

  add_exit(DUN_DIR+"road/r11","northwest",0);
  add_exit(DUN_DIR+"road/r09","southeast",0);
/*
  add_exit(DUN_DIR+"forest/f02","north",0);
*/

  make_the_room();
}

query_road()
{
 return 1;
}

reset_room()
{
}

