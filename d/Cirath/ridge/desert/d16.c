 /* The desert, just west of Tyr.
  * Dethraine, March, 1998. Code (c) Damian Horton.
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{

  set_short("A harsh and forbidding wilderness, just west of Tyr.");
  set_long("A harsh, forbidding wilderness, west of Tyr. "+
        "The landscape is almost entirely devoid of vegetation, "+
        "with bare rock, and earth being the norm. Gusts of wind "+
        "raise clouds of the reddish dirt which sweep their way "+
        "across the barren landscape. To the west, the red forms "+
        "of the Ringing mountains dominate the horizon. To your "+
        "north and west you see splatches of yellow, and even "+
        "a little green - the agricultural fields which feed the "+
        "city of Tyr.\n");

  add_item(({"crops","plants","crop","field","fields","green"}),
        "You are too far away to get a good view, but it is "+
        "apparent from the yellowish tinge, that the crops "+
        "surrounding Tyr are not in the best of health.\n");

  add_item(({"clouds of dirt","wind","clouds"}),
      "Across this more or less flat portion of Athas, the wind "+
      "blows almost constantly, raising great clouds of reddish "+
      "brown dirt. These clouds sting the eyes and nose, "+
      "and obscure vision signifigantly wherever they arise.\n");

  add_item(({"mountains","Mountains","Ringing Mountains",
        "Ringing mountains","ringing mountains"}),
        "Stark and majestic, the Ringing mountains rise to the "+
        "east. From here you can also make out the twin arcs "+
        "which emanate from the central mountain range and "+
        "extend north and south of the city of Tyr.\n");

  add_item(({"dirt","ground","rock","bare rock"}),
      "You examine the ground, but, not surprisingly, find nothing "+
      "of interest.\n");

  add_exit(RIDGE_DESERT+"d17.c","east",0,8,0);
  add_exit(RIDGE_DESERT+"d13.c","northeast",0,12,0);
  add_exit(RIDGE_DESERT+"d12.c","north",0,8,0);
  add_exit(RIDGE_DESERT+"d11.c","northwest",0,12,0);
  add_exit(RIDGE_DESERT+"d15.c","west",0,8,0);
/*  add_exit(RIDGE_DESERT+"d19.c","southwest",0,12,0);
    add_exit(RIDGE_DESERT+"d20.c","south",0,8,0);
    add_exit(RIDGE_DESERT+"d21.c","southeast",0,12,0);
*/
}


