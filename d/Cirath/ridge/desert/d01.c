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

  set_short("Near the foothills of the Ringing Mountains");
  set_long("A harsh, forbidding wilderness, which becomes "+
	"increasingly hilly, and treacherous to the north and "+
	"west, where the foothills of the ringing mountains arise. "+
 	"The landscape is almost entirely devoid of vegetation, "+
	"with bare rock, and earth being the norm. Gusts of wind "+
	"pick up clouds of dirt which sweep across the barren "+
	"landscape. Spatches of green color the landscape to the "+
	"west - the fields of crops which surround the city of "+
	"Tyr.\n");


  add_item(({"crops","plants","crop","field","fields","green"}),
	"You are too far away to get a good view, but even at this "+
	"distance, the crops do not appear to be very healthy. "+
	"Still, it is this desperate, labour and resource intensive "+
	"agriculture which feeds the citizens of Tyr.\n");

  add_item(({"mountains","mountain","Ringing Mountains",
	"Ringing mountains","ringing mountains"}),
	"Stark and majestic, the Ringing mountains rise to the "+
	"east. To your north, one arc of the mountains also "+
	"towers skyward, while far to the southeast, you can "+
	"see another arc of the mountains jutting outwards into "+
	"the Athasian wastes.\n");

  add_item(({"foothills","hills"}), "To the west and north, the "+
	"terrain becomes increasingly hilly and rocky. Beyond "+
	"the hills, and towering majestically and threateningly "+
	"over them are the Ringing mountains.\n");

  add_exit(RIDGE_DESERT+"d02.c","east",0,8,0);
  add_exit(RIDGE_DESERT+"d05.c","southwest",0,8,0);
  add_exit(RIDGE_DESERT+"d06.c","south",0,8,0);
  add_exit(RIDGE_DESERT+"d07.c","southeast",0,8,0);

}


