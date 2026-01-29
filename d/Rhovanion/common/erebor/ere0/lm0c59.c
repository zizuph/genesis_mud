inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a path southwest of Lovely Mountain.\n");
    set_long(
    "You are standing on the otherside of the River Running, just to your " +
    "east on the otherside of the River Running you see a small path leading " +
    "towards the great Front Gate of Lonely Mountain. The River Running flows " + 
    "from inside the mountain pass you and towards the south towards the Long " +
    "Lake. Somewhat to the southwest you can spot RavenHill.\n");
    
    add_item(({"river", "running"}),BS(
    "The river runs rapid in a deep canal to the east of you. Diving " +
    "into it probably would get you killed in no-time!\n"));    
    
    add_item("canal",BS(
    "The canal is too wide to jump across and it looks to deep to " +
    "wade, besides the walls of the canal are all smooth so where " +
    "would you get the grip to descend anyway?\n"));
    
   
    add_exit(CAVE_DIR+ "lm0c58","southwest"); 

}

