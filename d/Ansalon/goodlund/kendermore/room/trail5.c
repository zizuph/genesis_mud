#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit KENDERMORE_OUT;

void
reset_kendermore_room()
{
}

create_kendermore_room()
{
    set_short("On a dirt road just east of a bridge");
    set_long("@@long_descr");

    add_item(({"city", "kendermore"}), "You can barely glimpse the city of " +
        "Kendermore to the east. It is the home of many kender when they are " +
        "not wandering Krynn.\n");
    add_item(({"bridge", "wooden bridge"}), "To the west, a wooden bridge " + 
        "spans over a merrily flowing river.\n");
    add_item(({"trail","dirt trail"}), "You stand upon a dusty road " + 
        "surrounded on both sides by a great evergreen forest.\n");
    add_item(({"forest","great forest","great evergreen forest",
        "evergreen forest"}), "The ancient oaks tower above you on " +
        "both sides of the forest, their branches meeting above you, " + 
        "partly blocking the sky. Underbrush grows heavily at the sides " + 
        "of the road, making it difficult, but not impossible to enter " + 
        "the great forest.\n");
    add_item("underbrush", "It grows heavily on the forest ground, " + 
        "creeping out into the road.\n");
    add_item(({"trees", "tree", "oaks", "oak", "ancient oaks"}), "They " + 
        "look as if they date from the Cataclysm.\n");
    add_item("branches", "They form a canopy above you, causing mottled " + 
        "shadows to fall on the ground.\n");
    add_item("sky", "It is partially blocked by the branches, but visible.\n");

    add_invis_exit(KROOM + "nowhere", "north", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "south", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@no_go");
    add_invis_exit(KROOM + "forest10", "east", 0);
    add_exit(KROOM + "trail4", "northeast", 0);
    add_exit(FFROOM + "bridge", "west", 0);

    set_tell_time(120);
    add_tell("A kender comes skipping along the trail loudly singing " + 
        "a popular trailsong.\n");
    add_tell("A strong breeze blows through the trees refreshing you.\n");
    add_tell("A small rabbit hops from the forest across your path.\n");

    reset_kendermore_room();
}

int
no_go()
{
    write("The undergrowth is too thick to walk in that direction.\n");
    return 1;
}

string
long_descr()
{
    return(tod_descr() + season_descr() + "You stand upon a dirt trail " + 
        "just to the west of Kendermore. A great evergreen forest stands " + 
        "on both sides of you. The trail leads deeper into the forest to " + 
        "east, and across a bridge to the west. You can hear the sounds of " + 
        "a merrily running river to the west.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


