inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Entryway to the citadel's courtyard");
   set_long("At the enterance to the citadel's courtyard.  Peeking past"
           +" the wall's gates you see the citadel itself cut into the"
           +" the caveren wall.  A large building occupies most of the"
           +" north side of the courtyard, all of which is lit up by some"
           +" magical light within.  There are two guard houses atop the"
           +" the wall on either side of the gate, maybe you can get the"
           +" attention of whoever is in there?\n");
   add_item(({"citadel"}),
      "The citadel has been cut into the cavern wall.  Some balconies over"
     +"look the courtyard.\n"); 
   add_item(({"wall"}),
      "This wall surrounds the citadel's courtyard.  It meets up with the"
     +" cavern wall here.  An obscure path follows the wall north.\n");
   add_item(({"houses", "guard houses", "house", "guard house"}),
      "The guard houses are connected by a long plank spanning over the"
     +" wall's gate.  Whoever is up there could possibly open the gate"  
     +" if you got their attention.\n");
   add_exit(CPASS(dwarf/citadel/c1),"west");
   add_exit(CPASS(dwarf/citadel/c11),"east");
   add_exit(CPASS(dwarf/citadel/c3),"north");
}

