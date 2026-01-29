inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Bruno */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Dwarven courtyard");
   set_long(" The cavern wall rises up into the empty darkness to the north."
           +" The air here still seems rather thick being filled with water"
           +" vapor emanating from the moist stone walls."
           +" It is rather dark here now that the building"
           +" stands between you and the illumination from the"
           +" globe.\n");
   add_item(({"globe","illumination","light"}),   
            "The courtyard is being illuminated by an unnatural light"
           +" source in the center of the courtyard.\n");
   add_item(({"building","stable"}),
            "An odor of manure is emanating from the building, it appears"
           +" to be some sort of stable.\n");
   add_item(({"cavern","wall"}),
            "The cavern is speckled with many different minerals reflecting"
           +" the erie light from the courtyard.\n");
   add_exit(CPASS(dwarf/citadel/c8),"west");
   add_exit(CPASS(dwarf/citadel/c15),"east");
} 
