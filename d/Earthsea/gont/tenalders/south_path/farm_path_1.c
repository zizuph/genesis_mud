#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

public void
create_earthsea_room()
{
    set_short("Farm path");
    set_long("The dirt path leads away from the road to a pair " +
        "of farm buildings to the north. On either side stands " +
        "a row of fruit trees, whose green-leaved boughs are laden with " +
        "golden peaches and red apples. You see a two-wheeled cart which " +
        "has been abandoned by the path, its dray poles resting up against " +
        "a tree. The donkey which had pulled the cart lies dead, and a " +
        "swarm of flies hovers around the rotting corpse.\n");
    add_item((({"farm buildings", "pair of farm buildings",
        "buildings"})),
        "Beyond the trees you see two farm buildings standing to the " +
        "north at the end of the path.\n");
    add_item((({"boughs", "green-leaved boughs","trees", "fruit trees"})),
        "The green-leaved boughs of the trees are laden with golden and " +
        "red fruit, which are a bit too high for you to reach.\n");
    add_my_desc("A corpse of a donkey.\n");
    add_item((({"corpse", "rotting corpse", "donkey"})),
        "The donkey, which does not appear to have died from old age, " +
        "met a sad fate on this path, as evidenced by the pitiful " +
        "remains. It looks like it had been brutally hacked, as with " +
        "an axe or a sword.\n"); 
    add_item((({"cart", "two-wheeled cart", "dray poles"})),
        "One of the cart wheels has been broken, and the dray poles " +
        "are tilted up uselessly resting against a tree.\n");
    add_cmd_item((({"tree", "fruit tree", "trees"})), "climb",
        "You try to climb the fruit tree, but fail.\n");
    add_item((({"flies", "swarm", "swarm of flies"})),
        "A nasty swarm of flies hovers around the donkey's corpse.\n");
    add_item((({"fruit", "peaches", "apples", "golden peaches",
        "red apples"})),
        "The fruit has been picked from the lower boughs, but you " +
        "can see golden peaches and red apples dangling on " +
        "higher boughs, tantalizingly out of your reach.\n");
    add_item((({"path", "dirt path"})),
        "The dirt path has signs of the passing of many feet.\n");
    add_exit("farmyard", "north");
    add_exit("cobbled_road5", "south");
}
