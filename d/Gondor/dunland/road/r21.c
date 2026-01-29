inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decrepit stone paved road";
 where = "north";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "tall yellowgreen grass";
 extraline = "You are on a high plateau extending as far as the eye can"
           + " see. All around you, the " +vegetation
           + " covers the high plains of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast. ";

 add_exit(DUN_DIR + "road/r22", "northwest", 0, 3);
 add_exit(DUN_DIR + "road/r20", "southeast", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

