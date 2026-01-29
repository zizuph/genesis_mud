/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include <macros.h>
inherit ISLE_BASE;

public void
create_khalakhor_room()
{
    proxim = (["meadow":({3, "west"}),
              "shore":({4, "west"}),
              "tower":({2, "east"})
                    ]);
    path = ({"north","southeast"});
    extra = "A soft breeze carries the sweet scent of pine. ";
    create_forest();
 
 
   add_exit("isl0303", "north");
   add_exit("isl0103", "south", 0, 0, 1);
   add_exit("isl0202", "west", 0, 0, 1);
   add_exit("isl0302", "northwest", 0, 0, 1);
   add_exit("isl0102", "southwest", 0, 0, 1);
   add_exit("isl0104", "southeast");
   add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");

}
int
do_lay(string str)
{

    if((str == "down") || (str == "path") || (str == "honeysuckle"))
    {
	write("The path isn't a good place to lay down so you "+
	  "change your mind.\n");
	say(QCTNAME(TP)+" examines the path carefully.\n");
	  
    return 1;
    }
    else
   {
    notify_fail("Lay down?\n");
    return 0;
   }
}

void
init()
{
    ::init();

   add_action(do_lay, "lay");
}
