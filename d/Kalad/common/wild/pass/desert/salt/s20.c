inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the salt flat");
   set_long("The Great Salt Flat spreads before you, its flat, empty "+
      "landscape the stuff of dreams...twisted ones. The ground is covered "+
      "in a seemingly endless, thick layer of salt crystals that goes on and "+
      "on until it disappears into the distant horizon. The cruel light of "+
      "the Kaladian sun reflects brightly off the crystals. Not a single "+
      "plant grows here, for this place is truly a wasteland.\n");
   add_item(({"flat landscape","empty landscape","landscape","great salt flat","great flat","salt flat","flat"}),
      "A burning hot wasteland within the greater wasteland of the Great Kalad "+
      "Waste.\n");
   add_item(({"distant horizon","horizon"}),"A thin line far in the distance.\n");
   add_item(({"ground"}),"Littering the ground are hundreds upon "+
      "hundreds of salt crystals, glinting in the harsh light.\n");
   add_item(({"thick layer","layer","salt crystals","salt crystal","crystals","crystal"}),
      "The formations of salt cover the ground in every direction you "+
      "look. Perhaps centuries ago, this was the site of a lake or other body "+
      "of water. Now however, it is nothing but a wasteland.\n");
   add_item(({"kaladian sun","sun"}),
      "As you gaze up at it, you are nearly blinded by its brilliance!\n");
   add_exit(CPASS(desert/salt/s21),"west",0,4);
   add_exit(CPASS(desert/salt/s29),"north",0,4);
   add_exit(CPASS(desert/salt/s19),"east",0,4);
   add_exit(CPASS(desert/salt/s14),"south",0,4);
}
