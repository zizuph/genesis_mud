inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("On the inside of the courtyard's gates");
   set_long("You stand between the courtyard's wall and west side"
           +" of a building.  There are some low pitched grunting"
           +" sounds emminating from within.  No visable enterance"
           +" is on this side.\n");
   add_item(({"building"}),
            "The building is made up of large marble blocks that have"
           +" been so highly polished you can see youself in them.\n"); 
   add_item(({"wall"}),        
            "The inside of the courtyards wall made up of granite"
           +" blocks cut to fit together so exact that they need"
           +" no cements.\n");
   add_exit(CPASS(dwarf/citadel/c9),"north");
   add_exit(CPASS(dwarf/citadel/c11),"south");
}
