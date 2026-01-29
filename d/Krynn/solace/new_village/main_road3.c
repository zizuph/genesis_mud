/*
 * The village Solace
 *
 * By Rastlin
 */
 
/* Last Updated
*  By: Leia
*  June 12, 2005
*/

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"
#include <macros.h>
#include <ss_types.h>

inherit SOLOUTROOM2;

string
climb_hole()
{


    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
        write("You dont think you are skilled enough to try and climb up to the building above.\n");
        say(QCTNAME(this_player()) + " looks a bit too scared to climb up to the building above.\n");
        return "";
    }
    write("You skillfully make your way up the tree and into the kitchen of an Inn.\n");
    TP->move_living("climbing up the tree and into the hole above.",KITCHEN,1,0);

    return "";
}

create_solace_room()
{
    set_place(MAINROAD);

    set_long_desc("The road twists and turns here, cutting through the " +
		  "dense vallenwood forest. High overhead, the limbs " +
		  "mesh to form a thick green canopy. The road continues " +
		  "both to the north and south, to the north you can see " +
		  "a high mighty vallenwood tree. Running above your " +
		  "head is a wooden bridge-walk. There is some rubbish laying here that has apparently been pushed through the hole in the floor of the building above you.");	  
    add_item("hole", "There is a rubbish hole in the building above you. Perhaps you can climb the tree up into it.\n");
    
    add_exit(TDIR + "main_road2", "north");
    add_exit(TDIR + "main_road4", "south");
    add_cmd_item(({"up hole","up rubbish hole","up","hole","tree","up tree","up vallenwood tree"}),"climb", "@@climb_hole");
}


