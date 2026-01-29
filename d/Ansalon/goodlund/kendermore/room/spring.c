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
    set_short("In the midst of an ancient forest by a clear spring");
    set_long("@@long_descr");

    add_item(({"forest","great forest","great evergreen forest",
        "evergreen forest"}), "The ancient oaks tower above you, their " +
        "branches meeting above, partly blocking the sky. Underbrush grows " + 
        "heavily on the forest floor, making it difficult, but not " + 
        "impossible to walk through the great forest.\n");
    add_item("underbrush", "It grows heavily on the forest ground.\n"); 
    add_item(({"trees", "tree", "oaks", "oak", "ancient oaks"}), "They " + 
        "look as if they date from the Cataclysm.\n");
    add_item("branches", "They form a canopy above you, causing mottled " + 
        "shadows to fall on the ground.\n");
    add_item("sky", "It is partially blocked by the branches, but visible.\n");
    add_item(({"spring", "ground"}), "The spring looks clear and " + 
        "sparkling, but you can sense a wrongness, something missing. You " +
        "heard somewhere that all springs and rivers had their own goddess " + 
        "or nymph. Perhaps this spring has nobody to tend to it.\n");
    add_item("water", "It looks good to drink.\n");

    add_cmd_item(({"to spring", "spring"}), "tend", "@@tend_spring");
 
    add_invis_exit(KROOM + "nowhere", "northeast", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "east", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "southeast", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "south", "@@no_go");
    add_invis_exit(KROOM + "nowhere", "southwest", "@@no_go");
    add_invis_exit(KROOM + "forest8", "west", 0);
    add_invis_exit(KROOM + "forest7", "northwest", 0);
    add_invis_exit(KROOM + "forest6", "north", 0);

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
tend_spring()
{
    if (TP->query_wiz_level())
    {
        write("This isn't your spring!\n");
        return "";
    }

    else
    {
        write("Only a goddess or a nymph can tend to this spring.\n");
        return "";
    }
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
    return(tod_descr() + season_descr() + "You stand in the midst of a " + 
        "great evergreen forest. Ancient oaks tower above you, and " + 
        "underbrush grows tangled on the ground, making travel slow. A " + 
        "clear peaceful spring bubbles up from the ground here.\n");
}

void
init()
{
    ::init();
    add_action("drink_water", "drink");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

int
drink_water(string str)
{
    NF("Drink what?\n");
    if ((str == "from water") || (str == "water") ||
        (str == "from spring") || (str == "water from spring"))
    {
        if (TP->drink_soft(TP->drink_max() / 16,0))
        {
            say(QCTNAME(TP) + " kneels down by the spring and drinks some " + 
                "water from a cupped hand.\n");
            write("You kneel down by the spring. Cupping your hand, you " + 
                "take a refreshing drink of water.\n");
        }
        else
            write("You can't hold anymore water!\n");
        return 1;
    }
    return 0;
}

