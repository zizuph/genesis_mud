inherit "/d/Gondor/common/lib/road";
#include "/d/Gondor/defs.h"

create_room() 
{
 street = "decrepit stone paved road";
 where = "central";
 county = "Dunland";
 land = "old Gondor";
 mountain = "Misty Mountains";
 vegetation = "bushy green aromatic hemp";
 extraline = "You are on a fertile plateau extending north as far as the"
           + " eye can see. All around you, the " +vegetation
           + " covers the land of " +county+ ". You see"
           + " an old road running in from the northwest and vanishing to the"
           + " southeast.";

 add_item((({"hemp","tall hemp","aromatic hemp","bluegreen hemp"})),
        "Itt looks as though this wild hemp isn't ready for harvest yet. Too bad.\n");

 add_exit(DUN_DIR + "road/r21", "northwest", 0, 3);
 add_exit(DUN_DIR + "road/r19", "southeast", 0, 3);

 make_the_room();
}

query_road()
{
 return 1;
}

