/*
 * Track in Evendim orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"

#include <macros.h>

inherit CAMP_BASE;
inherit ENTER_BASE;

#define MIN_AWARE 15 + random(5)
#define EVENDIM_BUSHES "_evendim_bushes_searched_"

void
create_camp_room()
{
	set_extraline("A well worn track runs throughout the camp, " +
        "connecting this area with other parts of the camp. " +
        "Scattered about the camp are large tents. Occasionally " +
        "an orc enters or leaves a tent and eyes you " +
        "suspiciously. Some bushes line the path north of here.");

	add_item(({"track","depression"}),"The track is a well worn " +
        "depression in the ground where countless feet have " +
        "passed by.\n");
    add_item(({"bushes"}),
        "They are old and scraggly and look like they have been " +
        "smashed down by many countless feet. Still, they seem " +
        "to be more crushed than other bushes in the area.\n");
    add_cmd_item("bushes","search","@@do_search@@");

//    add_exit(CAMP_DIR + "track15", "north", "@@check_exit@@"); 
    add_exit(CAMP_DIR + "track15", "north", "@@block_me@@");
	add_exit(CAMP_DIR + "track12", "south");
	add_exit(CAMP_DIR + "track13", "southeast");
	add_exit(CAMP_DIR + "track11", "southwest");

    set_tent_name("tent14");
	reset_shire_room();
}

void reset_shire_room()
{
    clone_warning_orcs();
}

/*
int check_exit()
{
    if (TP->query_prop(EVENDIM_BUSHES))
    {
  	    TP->move_living("M", CAMP_DIR + "track14");

    }
    else
        write(" You don't see a way through the bushes that " +
        "way.\n");
    return 0;
}
*/
    
/*

string
do_search(object searcher, string str)
{
   int awareness;

   awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE) return 0;
    if(!str || (str!= "bushes")) return 0;
    TP->add_prop(EVENDIM_BUSHES,1);
    say(QCTNAME(searcher)+ " searches the bushes.\n");
    return "You notice that the bushes have been stamped down, forming a path leading north.\n";
}
*/

int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

        write("Hidden orcs guard the other side of the " +
            "bushes. They prevent you from going that way.\n");
    return 1;
}
