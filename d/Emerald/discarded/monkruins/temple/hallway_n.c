inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
   add_prop(ROOM_I_INSIDE, 1);
   set_short("Northern hallway");
   set_long("   You are standing in the hallway overlooking a "+
            "courtyard to the east. In the centre of the courtyard you can "+
            "see a well. You can hear a constant drone coming from the "+
            "hall of the temple to the south.\n\n");

   add_exit(TEMPLE_DIR + "hall", "south", 0);
   add_exit(TEMPLE_DIR + "court_nw", "east", 0);
 
   add_item("well","It just looks like a normal well, rounded stone.\n");
}
