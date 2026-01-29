/**********************************************************************
 * - pie01205.c                                                     - *
 * - The Riddler is here. She gives entrance quest to Galaith Isle. - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 * - Adjusted to the new bits and system Tapakah 09/2021            - *
 **********************************************************************/

#pragma strict_types


#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"
#include "../defs.h"
#include "../npc/riddler.h"

inherit PIER_ROOM;
inherit "/d/Khalakhor/common/room/samorgan-galaith-exit";

object riddler;

int *
query_local_coords ()
{
  return ({12, 5});
}

void
reset_pier ()
{
  if (!riddler) {
    riddler = clone_object(NPC + "riddler");
    riddler->move(this_object(), 1);        
  }
}

void
create_pier ()
{
  add_exit("pie1204", "west");
  add_exit("pie1305", "south");
  add_exit("pie1105", "north");
  add_exit("pie1206", "east", check_exit, 0, show_exit);
  reset_pier();
}
