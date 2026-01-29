/*
 * coded by Amelia 8/2/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";
inherit "/d/Earthsea/gont/tenalders/high_fall/climb";

public void
create_earthsea_room()
{
    set_short("By a waterfall");
    set_long("A precarious perch not far from a vast " +
        "waterfall to your north. You are on the ledge of " +
        "a cliff that goes straight up into mist-shrouded " +
        "heights. To the west a suspended rope bridge sways " +
        "in the breeze created from the torrent. Far below " +
        "white water swirls in a dangerous maelstrom.\n");
    set_next_up("/d/Earthsea/gont/tenalders/high_fall/cliff1");
    set_next_down("at_bottom");
    add_item((({"cliff", "ledge", "perch"})),
        "You are standing on a narrow ledge at the base " +
        "of a tall limestone cliff that ascends into a " +
        "cloud of mist.\n");
    add_item((({"ravine", "bridge", "rope bridge"})),
        "Directly to the west is an old frayed rope " +
        "bridge that sways in every breeze.\n");
    add_item((({"waterfall", "maelstrom"})),
        "To the north is a large waterfall " +
        "that pours its waters into a swirling river far " +
        "below.\n");
    add_item((({"mist", "cloud of mist"})),
        "The tall cliff is shrouded in mist, so that it is " +
        "you cannot see where it ends.\n");
    add_tell("The roaring sound of water hurts your ears.\n");
    add_tell("You are surrounded by a cloud of mist.\n");
    add_tell("You see a rainbow arc through the mist.\n");
    reset_room();
    set_tell_time(30);
    add_exit("bridge5", "west", 0, 2, 0);
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
