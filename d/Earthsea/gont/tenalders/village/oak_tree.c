/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <macros.h>
#include <ss_types.h>

public void
create_earthsea_room()
{
    set_short("Oak tree");
    set_long("You find yourself among the thick branches of " +
        "an old oak tree. The leaves of the tree filter out most " +
        "of the sunlight here, making this a shady room. Far out on " +
        "a limb you spot a small bird's nest.\n");
    add_item((({"leaves", "tree", "room", "shady room", "branches",
        "leafy branches"})),
        "The leafy branches of the oak tree arch over you like " +
        "a ceiling. One limb extends far out, where you see a small " +
        "bird nest.\n");
    add_item((({"nest", "bird's nest", "small bird's nest"})),
        "You spot a small bird's nest out on the limb, but you " +
        "are too far away to examine its contents.\n");
    add_item("limb",
        "There is a limb that extends out, which has a small " +
        "bird nest anchored in its twigs. You might be able to climb " +
        "out on it, if you are careful.\n");
}

public int
climb(string str)
{
    object tp = this_player(), to = this_object();

    if(str == "on limb" || str == "out on limb" ||
        str == "limb")
    {
        if((tp->query_stat(SS_DEX) < 15) &&
            (tp->query_skill(SS_CLIMB) < 15))
        {
            write("You try to climb out on the limb, " +
                "but suddenly you lose your balance and fall!\n");
            tell_room(to, QCTNAME(tp) + "tries to climb out on " +
                "the limb but suddenly falls!\n", ({ tp }));
            tp->move_living("M",
                "/d/Earthsea/gont/tenalders/village/witch_garden_8", 1);
            tell_room(environment(tp), QCTNAME(tp) + " falls in.\n",
                ({ tp }));
            return 1;
        }

        write("You carefully climb out on the limb.\n");
        tell_room(to, QCTNAME(tp) + " carefully climbs out " +
            "onto the limb.\n", ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/village/limb", 1);
        tell_room(environment(tp), QCTNAME(tp) + " eases in.\n",
            ({ tp }));
        return 1;
    }

    if(str == "down" || str == "down the tree")
    {
        write("You climb down the tree.\n");
        tell_room(to, QCTNAME(tp) + " climbs down the " +
            "tree.\n", ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/village/witch_garden_6", 1);
        tell_room(environment(tp), QCTNAME(tp) + " climbs down from " +
            "the oak tree.\n", ({ tp }));
        return 1;
    }

    return notify_fail("Climb where?\n");
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
}
