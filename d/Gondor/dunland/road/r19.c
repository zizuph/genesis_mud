inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decrepit stone paved road";
 where = "central";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "tall bluegreen aromatic hemp";
 extraline = "You are on a fertile plateau extending north as far as the"
           + " eye can see. To the north and west, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast. To the southeast you see a marsh and an"
           + " old bridge across a stream.";

 add_item((({"hemp","tall hemp","aromatic hemp","bluegreen hemp"})),
        "It looks as though this hemp is being cultivated for rope. Too bad.\n");

 add_exit(DUN_DIR + "road/r20", "northwest", 0, 3);
 add_exit(DUN_DIR + "road/r18", "southeast", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

