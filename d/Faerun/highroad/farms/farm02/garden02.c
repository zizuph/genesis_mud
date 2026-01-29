/*
 * Farm flower garden
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_GARDEN;
inherit BASE_COMMON;

object ob;

void
create_garden_room()
{
    
    set_short("A large flower garden");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("The garden is lush and full of beautiful flowers. A " +
        "stone wall surrounds it, keeping out farm and wild animals. A " +
        "large farm house stands to the south. A path winds through " +
        "the flowerbeds, heading west and south.");


    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded flowerbeds. It is whitewashed " +
        "and sits at the southern edge of the garden.\n");
    
    reset_room();

    add_exit(FARM2_DIR + "garden01", "west");
    add_exit(FARM2_DIR + "garden03", "south");
    
//    add_prop(OBJ_S_SEARCH_FUN, "do_search");


}

void reset_room()
{
    ::reset_room();
}
