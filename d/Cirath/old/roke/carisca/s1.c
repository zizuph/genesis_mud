/*
 * s1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Stone pillar in volcano");
    set_long("You stand on a small landing at the bottom of the pillar.\n" +
             "There is a small staircase leading up to an ancient altar " +
             "standing on the top. All around the landing you see nothing " +
             "but a minor ocean of flaming inferno. Even though the lava " +
             "is really hot, you still feel that you could go both north " +
             "and south. You can also climb up to the altar.\n");

    add_exit("l1", "north");
    add_exit("l2", "south");
    add_exit("s2", "up");
}

int
dive()
{
    notify_fail("Nah, you don't dare...The lava looks too hot.\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(dive, "dive");
}
