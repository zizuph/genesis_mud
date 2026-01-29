/*
 * Guard tower in Sa Morgan - top level
 * Pretty mundane stuff
 * Tapakah, 04/2021
 */

#pragma strict_types

#include "../defs.h"

inherit SM_TOWER_BASE;

public int *
query_local_coords()
{
  return ({11, 9});
}

public int *
query_global_coords()
{
  return SAMORGAN_COORDS;
}

public void
create_khalakhor_room ()
{

  set_short("Guard tower, landing");
  set_long("This is the upper landing of Sa Morgan's guard tower. There is "+
           "a fence about six feet tall around the landing with narrow slits "+
           "for observation and for archers' usage at the time of need. "+
           "You can see the village of Sa Morgan bustling down below.\n");

  configure_samorgan_guard_tower("up", ({
                                   ({"tower-se", "down"}),
                                 }));
}
