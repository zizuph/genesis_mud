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
              "shore":({4, "north"}),
              "tower":({4, "southwest"})
                    ]);
   
    extra = "A soft breeze carries the sweet scent of pine. ";
    create_forest();
    add_item(({"blanket", "lush grass", "grass", "soft grass"}), lay_desc);
    add_my_desc(lay_desc, this_object());    
  add_exit("isl0607", "north", 0, 0, 1);
  add_exit("isl0407", "south", 0, 0, 1);
  add_exit("isl0506", "west", 0, 0, 1);
  add_exit("isl0508", "east", 0, 0, 1);
  add_exit("isl0606", "northwest", 0, 0, 1);
  add_exit("isl0608", "northeast", 0, 0, 1);
  add_exit("isl0406", "southwest", 0, 0, 1);
  add_exit("isl0408", "southeast", 0, 0, 1);
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
      
}
public void
init()
{
    ::init();
    init_lay();
}
