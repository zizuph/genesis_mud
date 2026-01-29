/*
 * Guard tower in Sa Morgan - ground level
 * Pretty mundane stuff
 * Tapakah, 04/2021
 */

#pragma strict_types

#include "../defs.h"

inherit SM_TOWER_BASE;

public int *
query_local_coords()
{
  return ({1, 0});
}

public int *
query_global_coords()
{
  return SAMORGAN_COORDS;
}

public void
create_khalakhor_room ()
{

  set_short("Guard tower, base level");
  set_long("This is the base level of Sa Morgan's guard tower. The room is "+
           "pretty spartan, with a table and a couple of benches in it. "+
           "Stairs lead up to the landing where the real watch happens. "+
           "You can see the village of Sa Morgan bustling outside the door.\n");

  configure_samorgan_guard_tower("ground", ({
                                   ({"vil0201", "southeast"}),
                                   ({"tower-nw-up", "up"}),
                                 }));
}
