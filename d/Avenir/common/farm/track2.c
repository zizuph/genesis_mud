#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/std/room";

void
create_room()
{
    set_short("A small path");
    set_long("You are following the path to the " +"@@query_dir@@");
    add_item("trees","You look at the trees and decide its probably " +
        "pines. From here you see the lake and some kind of a " +
        "building at the brink.\n");
    add_item("path","You feel the small path between your feet. It has " +
        "not been used during the last years and its all cowered with pine " +
        "needles.\n");
    add_item(({"needles","pine needles"}),"You kneel down and take a handful " +
        "of the pine needles. They are brown and dry and you let them slowly " +
        "glide through your fingers down on the path again.\n");
    add_item("building","You stretch in all your length to try to " +
        "determine what kind of a building it is. From here it looks " +
        "like a boathouse.\n");
    add_item("lake", "Between the trees you catch a glimpse " +
        "of the lake.\n");
    add_item("boathouse", "You cannot see much of the boathouse from here.\n");
    add_exit("track1","west");
    add_exit("track3","northeast");
    reset_room();
}

void
reset_room()
{

}

string
query_dir()
{
    string str;
    str = TP->query_prop(LIVE_S_LAST_MOVE);
        if (str == "east")
        {
            return "east from the hedge.\n";
               }
        if (str == "southwest")
        {
            return "southwest from the boathouse.\n";
        }
        return " boathouse.\n";
}

