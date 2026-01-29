/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */


#include "/d/Shire/sys/defs.h"
#include "local.h"

// inherit ROAD_BASE;
inherit "/std/room";

int coronet_found = 0;
string road_type = "path";


void
// create_road_room()
create_room()
{
    //set_areadesc("hollow");
    //set_area("circle in");
    //set_areaname("the Barrow Downs");
    //set_land("Eriador");

    set_long("This is an excavated hill in the valley of the " +
        "Downs. It is bowl shaped and looks like it was used for " +
        "cremating bodies or something. A tall rock stands tall " +
        "beneath the sky. This hollow circle has an uneasy feeling " +
        "about it.");

    add_item(({"tall rock", "rock", "tall stone", "stone"}),
        "The tall stone stands in the mids of the hollow. It " +
        "looks featureless yet somehow significant, as if it was " +
        "a landmark of some sort.\n");
    add_item(({"circle", "hollow circle", "ground"}),
        "The hollow circle is bowl shaped and looks like it was " +
        "excavated by someone ages ago. It is covered with green " +
        "grass with only a single tall rock rising from its center.\n");
    add_item(({"excavated hill"}),
        "The excavated hill is bowl shaped, and sunk into the " +
        "earth. The inside of the hil is covered with green grass. " +
        "A tall rock stands in the center and points to the sky.\n");

    add_exit(VAL_DIR + "val06", "north");
    add_exit(VAL_DIR + "val05", "southwest");

    add_prop(OBJ_S_SEARCH_FUN, "find_crown");
    add_prop(OBJ_I_SEARCH_TIME, 5);

}


reset_room()
{
    ::reset_room();
    coronet_found = 0;
}


public string
find_crown(object player, string str)
{
    object coronet;
    seteuid(getuid());
    write("coronet_found=" + coronet_found + "\n");
    write("str=" + str + "\n");

    if(str=="here" || str == "" || str == "ground")
    {
        if(coronet_found==0)
        {
            coronet = clone_object("/d/Shire/scav_hunt/coronet");
            coronet->move(player);
            coronet_found = 1;
            write("coronet_found=" + coronet_found + "\n");
            return "You find an ancient crown!\n";
        }
        return "You find nothing of interest there.\n";
    }


    return "You find nothing like that.\n";

}
