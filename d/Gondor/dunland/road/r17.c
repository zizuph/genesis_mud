inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decaying stone paved road";
 where = "central";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "long damp green grass";
 extraline = "You are on a fertile plateau extending east as far as the"
           + " eye can see. To the south and east, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the west and turning to the"
           + " southeast. Further to the west is a marsh and an old bridge.";

 add_exit(DUN_DIR + "road/r18", "west", 0, 3);
 add_exit(DUN_DIR + "road/r16", "east", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

