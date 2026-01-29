/**********************************************************************
 * - Galaith isle room                                              - *
 * - Created by Damaris 01/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types
#include "defs.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include <macros.h> /* For the Q macros in messages.. */
inherit ISLE_BASE;

public void
create_khalakhor_room()
{
    proxim = (["meadow":({3, "north"}),
              "shore":({4, "north"}),
              "tower":({4, "south"})
                    ]);
    path = ({"northeast","south"});
    extra = "There is an odd shaped tree here. A soft breeze carries "+
      "the sweet scent of pine. ";
    create_forest();
    add_item(({"odd tree", "odd shaped tree"}),
      "It is shaped oddly. It has a large round base, which seems out "+
      "of place among all the slender pines that fill this dense forest.\n");
    add_item(({"base", "large round base", "round base", "base of tree"}),
      "The odd shaped tree has a large round base that has some bark peeling. "+
      "Perhaps if you peeled the bark you could see more.\n");
    add_item(({"bark"}),
      "The bark looks like it is peeling away from the tree.\n");
    add_exit("isl0605", "north", 0, 0, 1);
    add_exit("isl0504", "west", 0, 0, 1);
    add_exit("isl0506", "east", 0, 0, 1);
    add_exit("isl0604", "northwest", 0, 0, 1);
    add_exit("isl0606", "northeast", 0, 0, 1);
    add_exit("isl0404", "southwest");
    add_exit("isl0406", "southeast");
    add_fail("auto", "Large rocks and blown debris across the path, makes the "+
      "shore inaccessible.\n");
}
int
peel_bark(string str)
{
    if (str != "bark")
    {
        notify_fail("Peel what?\n");
        return 0;
    }

    write("You peel back a piece of bark from the odd shaped tree "+
      "and suddenly you're pulled within it.\n");
     say(QCTNAME(this_player())+" does something then disappears.\n");

//    this_player()->move_living("M", "/d/Khalakhor/inisi/galaith/room/tree", 1, 0);
    this_player()->move_living("M", "/d/Khalakhor/inisi/galaith/room/tree", 1, 0);

    say(QCTNAME(this_player())+" suddenly appears.\n");
    return 1;
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

    add_action(peel_bark, "peel");
   add_action(do_lay, "lay");
}


