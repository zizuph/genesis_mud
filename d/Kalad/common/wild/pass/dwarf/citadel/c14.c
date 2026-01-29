inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Dwarven courtyard");
   set_long("You stand in the shadow of the east side of a building"
           +" within the dwarven courtyard."
           +" There are some low pitched grunting"
           +" sounds emminating from within.  No visable enterance"
           +" is on this side.  The courtyard continues to the north"
           +" and a small trail leads off the compacted"
           +" dirt of the courtyard to the east.\n");
   add_item(({"courtyard","globe","light"}),   
            "The courtyard is being illuminated by an unnatural light"
           +" source in the center of the courtyard.\n");
   add_item(({"building","stable"}),
            "An odor of manure is emanating from the building, it appears"
           +" to be some sort of stable.\n");
   add_item(({"dirt"}),
            "Its dirt!\n");
   add_exit(CPASS(dwarf/citadel/c15),"north");
   add_exit(CPASS(dwarf/citadel/c13),"south");
   add_exit(CPASS(dwarf/citadel/c17),"east");
}

