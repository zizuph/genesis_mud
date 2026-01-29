inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("A well worn road");
   set_long("You are standing on a well worn road leading down into a large"
           +"cavern wall.  Within it appears to be some sort of citadel."
           +"  There is a large globe of light atop of a pole illuminating"
           +" the front gate and the citadel's courtyard.\n");

   add_item(({"citadel"}),
           "The features of a citadel have been cut directly into the"
          +" cavern's wall.\n"); 
   add_item(({"courtyard"}),        
           "The courtyard can just barely be seen beyond a large wall"
          +" surrounding the citadel and is being lit up by some"
          +" unnatural light source.\n");
   add_item(({"road"}),
           "This road is made up of a series of bricks, but have since"
          +" been covered over by debris and dirt.\n");
   add_exit(CPASS(dwarf/citadel/c2),"east");
}
