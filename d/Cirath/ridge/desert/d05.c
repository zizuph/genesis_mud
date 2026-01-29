 /* The desert, just west of Tyr.
  * Code (c) Dethraine 1998.
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{
  set_short("On a road, west of Tyr."); 
  set_long("On a road of packed red Earth. The road heads "+
        "east towards Tyr, while to the northwest it becomes more "+ 
        "of a path as it rises gently into the foothills of the "+
        "Ringing mountains. The road cuts across a harsh and "+
        "forbidding wilderness.The landscape is almost entirely "+
        "devoid of vegetation, with bare rock, and earth being the "+
        "norm. Gusts of wind pick up clouds of dirt which sweep "+
        "across the barren landscape. The terrain appears to become "+ 
        "even more rigorous to the north and west, as one would "+
          "approach the stark red forms of the Ringing Mountains.\n");

  add_item(({"mountains","Mountains","Ringing Mountains",
        "Ringing mountains","ringing mountains"}),
        "Stark and majestic, the Ringing mountains rise to the "+
        "west. To your north, one arc of the moutains also "+
        "towers skyward, while far to the southwest, you can "+
        "see another arc of the mountains jutting outwards into "+
        "the Athasian wastes.\n");

  add_item(({"foothills","hills"}),"To the west and north, the "+
        "terrain becomes increasingly hilly and rocky. Beyond "+
        "the hills tower the majestic and threatening forms of "+
        "Ringing Mountains.\n");

  add_item("road","Its more of a path of packed red earth.\n");

  add_exit("/d/Cirath/wild/pass/pass01","west",0,4,0);
  add_exit(RIDGE_DESERT+"d06.c","east",0,4,0);
  add_exit(RIDGE_DESERT+"d01.c","northeast",0,9,0);
  add_exit(RIDGE_DESERT+"d10.c","southeast",0,9,0);
}


