inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by .... */
 
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Dwarven courtyard");
   set_long("You stand on a well worn path in the southeast corner of the"
           +" courtyard. The path continues to the northeast towards the dwarven"
           +" citadel carved directly into the cavern wall.  All around you"
           +" the cavern walls rise straight up into the darkness."
           +"  Particulate matter in the air is illuminated by an irridesent"
           +" globe.  To the north the courtyard sits in the shadow of the"
           +" stable.\n");
   add_item(({"cavern","wall"}),
            "The stone here, extremely course in texture, is made up of"
           +" dark micas that sparkle in the dim light.\n");
   add_item(({"courtyard","globe","light"}),   
            "The courtyard is being illuminated by an unnatural light"
           +" source in the center of the courtyard.\n");
   add_item(({"building","stable"}),
            "An odor of manure is emanating from the building, it appears"
           +" to be some sort of stable.\n");
   add_item(({"citadel"}),  
           "The features of a citadel have been cut directly into the"
           +" cavern's wall.\n");  
   add_exit(CPASS(dwarf/citadel/c10.c),"west");
   add_exit(CPASS(dwarf/citadel/c14.c),"north");
   add_exit(CPASS(dwarf/citadel/c17.c),"northeast");
}
 
