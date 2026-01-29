/* created by Aridor 06/21/93 */

#include "../local.h"
#include "../dragon/local.h"

inherit OUTSIDE_BASE;

void
create_splains_room()
{
    set_short("Pier on the Vingaard River");
    set_long("This is a pier on the Vingaard River. It looks " +
	     "like ships can land here to load and unload, but " +
	     "the pier itself is mostly deserted except for a sign " +
	     "hanging from a pole at the waterfront and a few barrels " +
	     "and crates stacked up, now slowly rotting away.\n");

    add_cmd_item("sign","read","You might be able to buy passage to " +
		 "Kalaman from here. " +
		 "Some handwriting underneath says: No guarantee can be " +
		 "given to your safety in Kalaman, the town is reportedly " +
		 "currently invaded.\n");
    add_item("sign","You might be able to buy passage to Kalaman from here. " +
	     "Some handwriting underneath says: No guarantee can be " +
	     "given to your safety in Kalaman, the town is reportedly " +
	     "currently invaded.\n");
    
    add_exit(ROOM + "ferry","southwest");
    add_exit(LANDING1, "north");
    add_exit(ROOM + "pier1", "south");
    
    add_item("pier",BS("It looks like ships can land here.",SL));
    add_item("river",BS("This is the mighty Vingaard River. You can "
         +   "hardly make out the other edge. It flows lazily to the "
         +   "north.",SL));
    add_item(({"barrels","crates"}),
	     "They are old and rotten, and you are certain there isn't anything " +
	     "of use in them anymore.\n");
}


