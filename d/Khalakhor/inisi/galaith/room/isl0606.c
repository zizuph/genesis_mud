/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"

inherit ISLEBASE;
#include "laying.c"
public void
create_khalakhor_room()
{
    proxim = (["shore":({1, "north"}),
               "forest":({1, "south"}),
               "tower":({4, "southwest"})
                    ]);
    extra = "A soft breeze carries the sweet scent of the sea. ";
    create_meadow();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    add_exit("isl0506", "south", 0, 0, 1);
  add_exit("isl0605", "west", 0, 0, 1);
  add_exit("isl0607", "east", 0, 0, 1);
  add_exit("isl0505", "southwest", 0, 0, 1);
  add_exit("isl0507", "southeast", 0, 0, 1);
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");

}
public void
init()
{
    ::init();
    init_lay();
}
