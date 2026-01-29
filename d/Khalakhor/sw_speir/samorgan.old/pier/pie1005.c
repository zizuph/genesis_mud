/**********************************************************************
 * - pie01005.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 * - Slightly modified for future developments by Tapakah, 04/2021  - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../defs.h"
#include <stdproperties.h>

inherit PIER_ROOM;
inherit UTILS;

object *workers;

#define X 10
#define Y 5

public int *
query_local_coords ()
{
  return ({X, Y});
}

public void
reset_room ()
{
  ::reset_room();
  reset_worker_team(3);
}

public void
create_pier ()
{
  string village_file = ROOM + sprintf("vil%02d%02d", X-1, Y);
  add_exit(village_file, "north");
  add_exit("pie1105", "south");
  set_alarm(0.5, 0.0, reset_room);
}
