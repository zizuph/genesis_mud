/*
 * orchard in Gont, with mackintosh apples
 * coded by Amelia, 4/13/98
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include <language.h>

private int num_apples = 0;

public void
create_herb_room()
{
    set_short("An apple orchard");
    set_long("All around are small green-leaved trees, " +
        "and you smell the delicious scent of apples. There is " +
        "a tall weathered grey pine barn standing just to the north. You " +
        "look up and see the loft where you entered here about " +
        "two meters above your head. The grassy knoll behind the " +
        "orchard to the south is surrounded by a wreath of thorn-covered " +
        "bushes.\n");
    add_item((({"trees", "small trees", "green-leaved trees",
        "apples"})),
        "The small green-leaved trees appear to be apple trees. " +
        "@@apples_picked");
    add_item((({"barn", "pine barn", "grey pine barn" })),
        "The tall barn blocks the way to the north, effectively " +
        "shutting off this small area. The walls of the barn " +
        "are made of weathered grey pine planks. As you look " +
        "more closely, you notice a rope dangling down from the " +
        "loft.\n");
    add_item((({"loft", "hay", "hay loft"})),
        "The hay loft is about two meters above your head. As you " +
        "look more closely, you notice that there is a rope dangling " +
        "down from it.\n");
    add_item((({"knoll", "grassy knoll", "thorn-covered bushes", 
        "bushes"})),
        "The bushes surrounding the grassy knoll are covered in " +
        "thorns, and it seems impossible to leave in that " +
        "direction.\n");
    add_item("ground",
        "The ground is covered with grass and apple leaves.\n");
}

public void
reset_room()
{
    num_apples = 0;
}

public string
apples_picked()
{
    if(num_apples >= 30)
    {
        return "The boughs are bare of apples.\n";
    }

    return "The boughs are covered with apples.\n";
}

public int
pick_apple(string str)
{
    object apple;

    if(!str || str != "apple")
    {
        return notify_fail("Pick what?\n");
    }

    if(num_apples >= 30)
    {
        return notify_fail("All the apples have been picked from the trees.\n");
    }

    num_apples++;
    apple = clone_object("/d/Earthsea/gont/tenalders/obj/items/good_apple");

    if(apple->move(this_player()))
    {
        apple->move(this_object());
        write("You try to pick an apple, but can't carry " +
            "any more and it drops to the ground.\n");
    } else {
        write("You pick " + LANG_ASHORT(apple) + " from " +
            "one of the apple trees.\n");
    }

    return 1;
}

public int
climb_up(string str)
{
    if(str == "rope" || str == "up rope" || str == "up the rope")
    {
        write("You climb up the rope.\n");
        this_player()->move_living("up the rope",
            "/d/Earthsea/gont/tenalders/south_path/loft", 1);
        return 1;
    } else if(str == "tree" || str == "apple tree") {
        return notify_fail("The trees are too small to climb.\n");
    }

    return notify_fail("Climb what/where?\n");
}

public void
init()
{
    ::init();
    add_action(pick_apple, "pick");
    add_action(climb_up, "climb");
    write("You fall down several meters onto the ground.\n");
}
