/*
 * Forest path leading to Wild Elves Guild
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "/d/Shire/cypress/thalandrone/local.h"

inherit FOREST_BASE;
inherit "/d/Shire/cypress/thalandrone/base_common";

string transport();

#define ROOMS_DIR   (WRUNNER_DIR + "rooms/")

string road_type = "clearing";

void
create_area_room()
{
    set_area("somewhere");
    set_areaname("in an ancient");
    set_land("forest");
    set_areatype(0);
    set_areadesc(road_type);


//    set_short("Outside an exquiste building");
    add_my_desc("You are deep within a large, ancient forest, " +
        "enshrouded by countless large trees, whose tops reach " +
        "for the sky. In the center are six giant cypress trees, " +
        "growing in a circle, and forming a portal. Swirling " +
        "mists blow out from the circle. A single beam of light " +
        "pierces the canopy to illuminate the circle of trees.\n" +
        "A circle of cypress trees.\n");

    add_item(({"portal", "cypress portal", "huge cypress portal",
            "huge portal", "circle", "circle of trees"}),
        "The circle of trees is made up of six cypress trees growing in a " +
        "circle. A single beam of light from the sky above " +
        "illuminates the center of the circle, casting an " +
        "ethereal look on the cypress trees. Mists swirl about " +
        "within the circle of trees.\n");
    add_item(({"cypresses", "cypress trees", "cypress"}),
        "The cypresses are ancient trees Their branches are a " +
        "rich green color and soft to the touch. The branches " +
        "grow up and out, forming a conical shape.\n");
    add_item(({"mists", "swirling mists"}),
        "The mists swirl about inside the portal. It coalesces " +
        "with some internal light, creating ethereal patterns. " +
        "Occasionally, some of the mists escapes from the portal, " +
        "drifting about and disappears.\n");
    add_item(({"beam of light", "light beam", "beam"}),
        "The beam of light comes from the sky, directly over the " +
        "portal, and illuminates it.\n");
    set_add_trees();
    set_add_forest_debris();

    add_cmd_item("portal",        "enter", "@@transport@@");
    add_cmd_item("portal",         "go",    "@@transport@@");
    add_cmd_item("through portal", "go",    "@@transport@@");


    add_exit(GLEN_DIR + "path01", "southwest");

}

void
init()
{   
    ::init();
    add_action("transport", "enter");
    add_action("transport", "go");
}



string transport()
{
    write("You enter the circle of trees. The mists suddenly envelope you " +
        "completely, and obscure your vision.\n");
    say(QCTNAME(TP)+ " enters the circle of trees, and suddenly " +
        "disappears into the mists.\n");
    TP->move_living("M", "/d/Genesis/start/elf/room/magestone_place",1);
    say(QCTNAME(TP) + " arrives in a swirl of sparkles, and steps " +
        "out of the circle of stones.\n");
    return "";
}
