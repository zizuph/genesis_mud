/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include <macros.h> /* For the Q macros in messages.. */
inherit ISLE_BASE;

public void
create_khalakhor_room()
{
    proxim = (["meadow":({3, "east"}),
              "shore":({4, "east"}),
              "tower":({2, "west"})
                    ]);
    path = ({"north","southwest"});
    extra = "A soft breeze carries the sweet scent of pine. ";
    create_forest();
 
 add_exit("isl0307", "north");
 add_exit("isl0107", "south", 0, 0, 1);
 add_exit("isl0208", "east", 0, 0, 1);
 add_exit("isl0308", "northeast", 0, 0, 1);
 add_exit("isl0106", "southwest");
 add_exit("isl0108", "southeast", 0, 0, 1);
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
