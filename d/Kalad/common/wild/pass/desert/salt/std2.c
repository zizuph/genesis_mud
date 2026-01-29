inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the salt flat");
   set_long("The Great Salt Flat, in all its desolate vastness, stretches "+
      "out before you. The ground all around you is completely covered "+
      "with salt crystals. Not a single green plant grows here, for the "+
      "heat of the Kaladian sun insures that no life will flourish. "+
      "Blinding in its intensity is the reflection of the sun off the "+
      "many crystals.\n");
   add_item(({"great salt flat","great flat","salt flat","flat","desolate vastness","vastness"}),
      "A burning hot wasteland within the greater wasteland of the Great Kalad "+
      "Waste.\n");
   add_item(({"ground"}),"Littering the ground are hundreds upon "+
      "hundreds of salt crystals, glinting in the harsh light.\n");
   add_item(({"salt crystals","salt crystal","crystals","crystal"}),
      "The formations of salt cover the ground in every direction you "+
      "look. Perhaps centuries ago, this was the site of a lake or other body "+
      "of water. Now however, it is nothing but a wasteland.\n");
   add_item(({"kaladian sun","sun"}),
      "As you gaze up at it, you are nearly blinded by its brilliance!\n");
}
