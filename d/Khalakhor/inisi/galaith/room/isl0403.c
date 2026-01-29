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
    proxim = (["meadow":({3, "west"}),
              "shore":({4, "west"}),
              "tower":({3, "southeast"})
                    ]);

    extra = "A soft breeze carries the sweet scent of pine. ";
    create_forest();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    add_exit("isl0503", "north", 0, 0, 1);
    add_exit("isl0303", "south", 0, 0, 1);
    add_exit("isl0402", "west", 0, 0, 1);
    add_exit("isl0404", "east", 0, 0, 1);
    add_exit("isl0502", "northwest", 0, 0, 1);
    add_exit("isl0504", "northeast", 0, 0, 1);
    add_exit("isl0302", "southwest", 0, 0, 1);
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
}
public void
init()
{
    ::init();
    init_lay();
}
