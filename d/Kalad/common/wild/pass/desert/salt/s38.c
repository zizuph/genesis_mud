inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the salt flat");
   set_long("The barren expanse of the Great Salt Flat lies all around you. "+
      "The ground beneath is encrusted with many dozens of salt crystals, "+
      "harshly reflecting the burning light of the Kaladian sun. No plant "+
      "life grows here, for this place is truly a wasteland.\n");
   add_item(({"barren expanse","expanse","great salt flat","great flat","salt flat","flat"}),
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
   add_exit(CPASS(desert/salt/s39),"north",0,4);
   add_exit(CPASS(desert/salt/s37),"east",0,4);
   add_exit(CPASS(desert/salt/s26),"south",0,4);
}
