/* Gladiator Row - street */
/* Made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   
   set_short("Gladiator Row");
   set_long(
      "Further northeast you are overwhelmed by the sight of a "+
      "huge arena! Many a gladiator has met his fate in that Circus of "+
      "death and bravery. All around the road you see slaves, "+
      "but still you note that there is a lot of work left for "+
      "them to do.\n");
   
   set_time_desc(
      "Several slaves works hard on fixing the road...but it goes slowly. " +
      "It will take some time before the arena will be ready for visitors.\n",
      "In this darkness, the slaves have stopped working, and lie "+
      "sleeping in the ditches beside the road.\n");
   
   hear_bell = 3; /* loud: outdoors in the central district */
   
   add_exit(CENTRAL(gladiator/s4),"southwest");
   add_exit(CENTRAL(arena/entrance_arena),"northeast");
   
}
