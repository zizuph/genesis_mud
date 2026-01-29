/*
 * /d/Gondor/harondor/base_road.c
 *
 * Contains basic descriptions for the harad road.
 * - Finwe, July 2005
 *
 * Modification log:
 *       2006.08.27: Fixed typo. Toby
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

public void add_harad_road_tells();

void add_all_road()
{

}

void add_desert()
{
    add_item(({"wasteland", "desert", "arid land", "ground", "land", "area"}),
        "The land is barren and dry. Very little grows here among the " +
        "rocks and sand except for dried grass. It is brown and parched, " + 
        "and very hot.\n");
    add_item(({"grass", "dried grass", }),
        "It is short and thin, and dried out. The grass is little more " +
        "than stubble in this wasteland.\n");
    add_item(({"rocks"}),
        "They are fragments of large rocks. They are chipped and hard " +
        "looking, and lay scattered across the arid wasteland.\n");
    add_item(({"sand", "grit"}),
        "These are small, loose grains of disintegrated rocks. They are " +
        "dark colored, making the ground look a dark color.\n");
}

void add_road()
{
    add_item(({"road", "highway"}),
        "The road is ancient looking and dusty. It is wide and made " +
        "centuries ago, and runs generally north and south.\n");
}

void add_ephel_duath(string str)
{

    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "slope", "slopes"}), "The peaks of the Ephel Duath " +
        "loom ominously in the distance. They look jagged and evil, " +
        "rising to the " + str + ".\n");
}


public void add_harad_road_tells()
{
    set_tell_time(120 + random(30));
    add_tell("Hot winds blow across the land.\n");
    add_tell("Some sand blows up into your eyes.\n");
    add_tell("Dark clouds blow across the sky.\n");
    add_tell("An evil looking bird flies overhead.\n");
    add_tell("A group of Haradrim march past you as they head north.\n");
    add_tell("A bird runs across the road in front of you and disappears.\n");

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

