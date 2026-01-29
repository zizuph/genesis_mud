/**********************************************************************
 * - pier2.c                                                        - *
 * - Created by Damaris 09/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Added a teaser, Tapakah 10/2021                                - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include "../defs.h"

inherit PIER_ROOM;

#define ISLE1 "/d/Khalakhor/inisi/galaith/room/isl0105"
#define TP this_player()

int *
query_local_coords ()
{
  return ({3, 5});
}

void
reset_pier ()
{
}

int
block_me ()
{
  TP->catch_msg("A wooden boom cuts the access to the construction site. "+
                "You read the label <MARINERS OF GENESIS> on the boom.\n");
  return 1;
}

void
create_pier ()
{
  add_exit(ISLE1, "north");
  add_exit("pier-mariners", "south", block_me);
  add_exit("pier1", "west");
  set_long(query_long() + "Some construction "+
           "has been started to the south.\n");

  reset_pier();
}
