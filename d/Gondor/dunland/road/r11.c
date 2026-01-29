inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decaying stone paved road";
 where = "east";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "tall yellowgreen grass";
 extraline = "You are on a grassy plateau extending south as far as the"
           + " eye can see. In all directions, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast. A small forest appears slightly to the east.";

 add_exit(DUN_DIR + "road/r12", "northwest", 0,3);
 add_exit(DUN_DIR + "road/r10", "southeast", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

