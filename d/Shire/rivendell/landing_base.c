/*
 * Base file for river Bruinen after it floods
 * By Finwe
 * July 1998
 */
 
#include "/d/Shire/sys/defs.h"
inherit AREA_ROOM;
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_landing_room() {}
 
 
public void
create_area_room()
{
    set_areaname("the river");
    add_item(({"river", "bruinen", "river bruinen", "water"}),
        "The river is relatively calm. Its silty water rushes " +
        "southwest, out of the mountains.\n");
    add_item(({"debris", "flotsam"}),
        "You see rotting logs, downed trees, large branches, " +
        "large boulders scattered about the riverbank, evidence " +
        "of the strength of the river.\n");
    add_item(({"rotting logs", "logs"}),
        "The logs are various sizes and splintered. They " +
        "look to be waterlogged, as if they floated down " +
        "the river. \n");
    add_item(({"downed trees", "trees", "trunks", "tree trunks"}),
        "Many of the trees look like they were ripped up from " +
        "the ground. Their roots are exposed and many of their " +
        "branches are broken from the wrath of the the river.\n");
    add_item(({"large branches", "broken branches"}),
        "You see broken branches of all sizes scattered around " +
        "the riverbank. Their ends are shattered from being " +
        "ripped from trees by sheer force of the river.\n");
    add_item(({"large rocks", "large boulders", "boulders"}),
        "Some large boulders are buried in the riverbed. Their " +
        "ends point out of the river, causing the river to " +
        "crash against them and creating whitewater.\n");
    add_item(({"riverbank", "shore"}),
        "The shore is littered with debris from the river.\n");

    create_landing_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}
 
string
landing_desc()
{
    switch(random(4))
    {
        case 0:
            return "Slowly, the river calms down and becomes " +
            "quiet. The force of the river has passed. All " +
            "around you are remnants of the fury of the river " +
            "that were washed down with it. Strewn around the " +
            "riverbank you see forest debris. A path leads north " +
            "from here. ";
            break;
        case 1:
            return "The river calms down and resumes its quiet " +
            "course southwest. Debris has been washed up onto " +
            "the shore. Scattered across the riverbank is flotsam " +
            "that has been carried down with the river. A path " +
            "leads north from here. ";
            break;
        case 2:
            return "Gradually, the river loses its fury, resuming " +
            "a quiet course southwest. All around you is debris " +
            "that has been washed down the river Bruinen. A path " +
            "leads north. ";
            break;
        case 3:
            return "Slowly, the river returns to a relaxed " +
            "state. Gently it laps at the riverbank. Debris " +
            "is scattered where the river has flooded its banks. " +
            "A path leads north from here. ";
            break;
 
        default:
            return "The river calms down and returns to its " +
            "normal course. Everywhere, debris lies scattered " +
            "acrossed the banks of the river. The river calmly " +
            "flows southeast. A path leads north. ";
            break;
     }
}

