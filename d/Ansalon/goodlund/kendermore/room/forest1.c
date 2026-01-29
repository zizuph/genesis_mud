/* Forest outside Kendermore, Gwyneth, June */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit KENDERMORE_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"decidforest", }) );

void
reset_kendermore_room()
{
    set_searched(random(2));
}

create_kendermore_room()
{
    set_short("In the midst of an ancient forest");
    set_long("@@long_descr");

    add_item(({"trail","dirt trail"}), "A dirt trail runs through the " + 
        "forest to your south and southwest.\n");
    add_item(({"forest","great forest","great evergreen forest",
        "evergreen forest"}), "The ancient oaks tower above you, their " +
        "branches meeting above, partly blocking the sky. Underbrush grows " + 
        "heavily on the forest floor, making it difficult, but not " + 
        "impossible to walk through the great forest.\n");
    add_item("underbrush", "It grows heavily on the forest ground, " + 
        "creeping out into the road.\n");
    add_item(({"trees", "tree", "oaks", "oak", "ancient oaks"}), "They " + 
        "look as if they date from the Cataclysm.\n");
    add_item("branches", "They form a canopy above you, causing mottled " + 
        "shadows to fall on the ground.\n");
    add_item("sky", "It is partially blocked by the branches, but visible.\n");

    add_cmd_item(({"tree", "oak tree"}), "climb", "@@climb_tree");
 
    add_invis_exit(KROOM + "nowhere", "east", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "north", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "northeast", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "northwest", "@@no_go");
    add_exit(KROOM + "trail2", "southwest", 0);
    add_invis_exit(KROOM + "forest2", "west", 0);
    add_exit(KROOM + "trail1", "south", 0);

    set_tell_time(120);
    add_tell("Odd sounds come from the hidden depths of the forest.\n");
    add_tell("A strong breeze blows through the trees refreshing you.\n");
    add_tell("A small rabbit hops across your path.\n");

    reset_kendermore_room();
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"underbrush","forest",}), 2);
}

string
climb_tree()
{
    write("You can't manage to reach even the lowest branch.\n");
    return "";
}

int
no_go()
{
    write("The underbrush is too thick to walk in that direction.\n");
    return 1;
}

string
long_descr()
{
    return(tod_descr() + season_descr() + "You stand in the midst of a " + 
        "a great evergreen forest. Ancient oaks tower above you, and " + 
        "underbrush grows tangled on the ground, making travel slow. A " + 
        "small dirt trail winds through the forest to the south and " + 
        "southwest.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


