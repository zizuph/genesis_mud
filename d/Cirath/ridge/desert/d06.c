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
  set_long("On am elevated road of packed red Earth. The road heads "+
	"east towards Tyr, and west, towards the daunting forms of the "+
	"Ringing mountains. The road cuts across a harsh and "+
	"forbidding wilderness.The landscape is almost entirely "+
	"devoid of vegetation, with bare rock, and earth being the "+
	"norm. Gusts of wind pick up clouds of dirt which sweep "+
	"across the barren landscape. The terrain appears to become "+ 
	"even more rigorous to the north and west, as one would "+
    "approach the stark red forms of the Ringing Mountains. "+
	"Spatches of green color the landscape to the "+
	"west - the fields of crops which surround the city of "+
	"Tyr.\n");

  add_item(({"crops","plants","crop","field","fields","green"}),
	"You are too far away to get a good view, but even at this "+
	"distance, the crops do not appear to be very healthy.\n");

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

  add_item("road","Its a road of packed earth, rising about 10ft above "+
      "the surrounding ground.\n");

  add_item(({"Tyr","city"}),"From here you can barely make out the "+
	"thick walls of the Citystate of Tyr.\n");

  add_exit(RIDGE_DESERT+"d07.c","east",0,4,0); 
  add_exit(RIDGE_DESERT+"d02.c","northeast",0,12,0);
  add_exit(RIDGE_DESERT+"d01.c","north",0,8,0);
  add_exit(RIDGE_DESERT+"d05.c","west",0,4,0);
  add_exit(RIDGE_DESERT+"d10.c","south",0,8,0);
  add_exit(RIDGE_DESERT+"d11.c","southeast",0,12,0);
}
