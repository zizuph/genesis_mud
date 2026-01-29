/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"

inherit ISLE_BASE;
#include "laying.c"
public void
create_khalakhor_room()
{
    proxim = (["meadow":({3, "north"}),
              "shore":({4, "west"}),
              "tower":({4, "southeast"})
                    ]);

    extra = "A soft breeze carries the sweet scent of pine. ";
    create_forest();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    add_exit("isl0603", "north", 0, 0, 1);
    add_exit("isl0403", "south", 0, 0, 1);
    add_exit("isl0502", "west", 0, 0, 1);
    add_exit("isl0504", "east", 0, 0, 1);
    add_exit("isl0602", "northwest", 0, 0, 1);
    add_exit("isl0604", "northeast", 0, 0, 1);
    add_exit("isl0402", "southwest", 0, 0, 1);
    add_exit("isl0404", "southeast", 0, 0, 1);
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
}
public void
init()
{
    ::init();
    init_lay();
}
