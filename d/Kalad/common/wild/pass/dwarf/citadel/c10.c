inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by .... */
 
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Dwarven courtyard");
   set_long("The air around you rests heavy on your shoulders, the humidity"
           +" here blankets your body.  You stand on a well worn path in the"
           +" courtyard that seems to lead eastwards towards the dwarven"
           +" citadel carved directly into the cavern wall.  All around you"
           +" the cavern walls rise straight up into the darkness."
           +"  Particulate matter in the air is illuminated by an irridesent"
           +" globe.  The enterance to the stables lies to the north.\n");
   add_item(({"cavern","wall"}),
            "The stone here, extremely course in texture, is made up of"
           +" dark micas that sparkle in the dim light.\n");
   add_item(({"courtyard","globe","light"}),
            "The courtyard is being illuminated by an unnatural light"
           +" source.\n");
   add_item(({"building",}),
            "An odor of manure is emanating from the building, it appears"
           +" to be some sort of stable.\n");
   add_exit(CPASS(dwarf/citadel/c6.c),"west");
   add_exit(CPASS(dwarf/citadel/c13.c),"east");
   add_exit(CPASS(dwarf/citadel/stable.c),"north");
}
