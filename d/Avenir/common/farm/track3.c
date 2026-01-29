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
    set_short("Outside the boathouse");
    set_long("You are standing outside a small boathouse. " +
        "The house is built on wooden poles and is surrounded " +
        "by high growing reed.\n");
    add_item("trees","You look at the trees and decide its " +
        "pines. From where you stand its impossible to see " +
        "the main house or any of the other buildings surrounding " +
        "it as the tress are blocking the view completely.\n");
    add_item("path","You feel the small path between your feet. " +
        "It has not been used during the last years and its all " +
        "cowered with pine needles.\n");
    add_item(({"needles","pine needles"}),"You kneel down and " +
        "take a handful of the pine needles. They are brown and " +
        "dry and you let them slowly glide through your fingers " +
        "down on the path again.\n");
    add_item("boathouse","You view the boathouse which is in " +
        "a strangly good shape. The small bricks on the roof " +
        "are all whole and neither of them are missing. Surrounding " +
        "the boathouse is thick and tall reed growing in the water.\n");
    add_item("reed","Swaying slowly in the wind, high reed " +
        "surrounds the boathouse. When you take a step to the side " +
        "you see that behind the boathose the reed opens up a bit " +
        "allowing a boat to enter the lake.\n");
    add_item("poles","You examine the poles a bit closer. They " +
        "all seem to be in a good shape and the water they stand " +
        "in, doesnt seems to change that fact.\n");
    add_item("lake","You try to catch a glimpse of the lake but " +
        "the boathouse and the thick reed cover your view.\n");
    add_item(({"roof","bricks"}),"The small bricks on the roof " +
                "are all whole and neither of them are missing.\n");
    add_exit("track2","southwest");
    add_exit("boathouse","in");
    reset_room();
}

void
reset_room()
{

}

