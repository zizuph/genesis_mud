/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    in_exit = BAR_DIR+"bar11_out";
    out_exit = VAL_DIR+"val15";

    set_areadesc("valley");
    set_area("below the");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("This is a valley at the southern end of the " +
        "Barrow Downs. Thick fogs and mists swirl about in a " +
        "hypnotizing manner, mesmerizing all who stumble here and " +
        "obscuring everything here. Occasionally they thin enough " +
        "to reveal a entrance. Around the entrance is dirt that " +
        "has piled up around.");
    add_item(({"hole", "entrance"}),
        "The hole, or entrance, leads into the barrow. It looks " +
        "like it was once an ancient entrance but now is nothing " +
        "more than a hole in the side of the hill.\n");
    add_item(({"dirt"}),
        "The dirt is piled up around the hole in the face of the " +
        "barrow. It is dark colored and looks like it's packed " +
        "down from many feet that have walked this way.\n");
    set_add_valley_descrs();

// if players haven't entered the valley by going through a 
// shaft, they can't go up into the shafts either nor see the 
// entrances.
//    add_exit("@@check_room@@", "up",0,0,"@@hole_check@@");
//    add_exit("@@check_quest@@", "east");
    add_exit(VAL_DIR + "val16", "south");
    add_exit(VAL_DIR + "val14", "northwest");

}
void
init()
{
    ::init();
    add_action("enter_hole", "enter");
}

int
enter_hole(string str)
{
    if(str=="hole" || str=="entrance" || str == "barrow" || str =="hill")
    {
        write("You cannot enter the barrow through the backway here. " +
            "You have not proven yourself strong enough to do that.\n");
        return 1;
    }
     
    NF("Enter what, the barrow? Not like that you can't.\n");
    return 0;
}


/*
 * Function name : check_quest
 * Arguments     : none
 * Description   : determines if player can go in and do quest
 */
string check_quest()
{
    if(this_player()->query_prop(BAR_SHAFT_EXIT) || 
        this_player()->query_wiz_level())
    {
        write("You enter the the mists and disappear.\n");
            return "/d/Gondor/common/quest/nv/edown";
    }
    else
    {
        write("Thick fogs and mists swirl about you, blinding " +
            "and confusing your movements.\n");
        return out_exit;
    }

}