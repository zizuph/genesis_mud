/*
 * Added a teaser, Tapakah, 10/2021
 */

#include "defs.h"
inherit PROAD;
 
int*
query_local_coords ()
{
  return ({16,6});
}
 
int
block_me ()
{
  TP->catch_msg("A wooden boom cuts the access to the construction site. "+
                "You read the label <MARINERS OF GENESIS> on the boom.\n");
  return 1;
}

void
create_khalakhor_room ()
{
  extra =
    "There is a small building of some kind to the north, while "+
    "you can walk out onto the pier to the east. Some construction "+
    "has been started to the south.";
  create_proad();
  add_item("building",
           "It is an old stone building with a thatched roof. It must "+
           "be a warehouse or pier office being so close to the pier.\n");
  add_exit("proad6", "west");
  add_exit("pier",   "east");
  add_exit("pierhouse","north");
  add_exit("pier-mariners", "south", block_me);
  
}
