/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"

inherit ISLEBASE;
#include "laying.c"
public int
block_exit()
{
    write("Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
    return 1;
}


public void
create_khalakhor_room()
{
    proxim = (["shore":({1, "east"}),
               "forest":({0, "west"}),
               "tower":({4, "southwest"})
                    ]);
    extra = "A soft breeze carries the sweet scent of the sea. ";
    create_meadow();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    add_exit("isl0509", "north", 0, 0, 1);
    add_exit("isl0309", "south", 0, 0, 1);
    add_exit("isl0408", "west", 0, 0, 1);
    add_exit("isl0508", "northwest", 0, 0, 1);
    add_exit("isl0308", "southwest", 0, 0, 1);
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");

}
public void
init()
{
    ::init();
    init_lay();
}
