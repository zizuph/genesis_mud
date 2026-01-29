inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("On the inside of the courtyard's gates");
   set_long("Inbetween the courtyard's wall and the north side of a"
           +" building.  It is rather dark here now that the building"
           +" stands between you and the illumination from the"
           +" courtyard.\n");
   add_item(({"building"}),
            "The building is made up of large marble blocks that have"
           +" been so highly polished you can see youself in them.\n"); 
   add_item(({"wall"}),        
            "The inside of the courtyards wall made up of granite"
           +" blocks cut to fit together so exact that they need"
           +" no cements. One block seems go have been chipped.\n");
   add_exit(CPASS(dwarf/citadel/c9),"west");
   add_exit(CPASS(dwarf/citadel/c14),"east");
}
