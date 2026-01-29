inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("On the inside of the courtyard's gates");
   set_long("On the inside of the courtyard's gates.  A globe of"
           +" unnatural light sitting on top of a tall pole provides"
           +" illumination for the courtyard.  A large statue stands" 
           +" in the middle of the courtyard to east and just beyond"
           +" that you can make out the citadel's enterance.\n");
   add_item(({"courtyard","globe","light"}),
            "The courtyard is being illuminated by an unnatural light"
           +" source.\n"); 
   add_item(({"citadel"}),        
            "The citadel has been cut into the cavern wall, some"
           +" balconies overlook the courtyard.\n");
   add_item(({"statue","enterance"}),
            "Its too far away to make out any details.\n");
   add_exit(CPASS(dwarf/citadel/c2),"west");
   add_exit(CPASS(dwarf/citadel/c10),"north");
   add_exit(CPASS(dwarf/citadel/c13),"east");
}

