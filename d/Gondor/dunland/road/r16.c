inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decaying stone paved road";
 where = "central";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "short yellowgreen grass";
 extraline = "You are on a fertile plateau extending as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the west and turning to the"
           + " southeast.";

 add_exit(DUN_DIR + "road/r17", "west", 0, 3);
 add_exit(DUN_DIR + "road/r15", "southeast", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

