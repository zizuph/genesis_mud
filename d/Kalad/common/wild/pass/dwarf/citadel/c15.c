inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by .... */
 
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Dwarven courtyard");
   set_long("You reached the northeast corner of the courtyard.  Beyond the"
           +" reaches of the courtyard's illumination you stare"
           +" into the vast darkness of this undergound world.   A cavern"
           +" wall towers over you to the north.  The backside"
           +" of the stables is to the west.\n");  
   add_item(({"courtyard","illumination","light"}),   
            "The courtyard is being illuminated by an unnatural light"
           +" source in the center of the courtyard.\n");
   add_item(({"building","stable"}),
            "An odor of manure is emanating from the building, it appears"
           +" to be some sort of stable.\n");
   add_item(({"citadel"}),  
           "The features of a citadel have been cut directly into the"
           +" cavern's wall.\n");  
   add_exit(CPASS(dwarf/citadel/c11.c),"west");
   add_exit(CPASS(dwarf/citadel/c14.c),"south");
}
