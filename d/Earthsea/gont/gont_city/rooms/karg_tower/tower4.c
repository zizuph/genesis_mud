#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

private object priestess, *guards = allocate(2);

public void
reset_room()
{
    object to = this_object();
    int i;

    if(!priestess)
    {
        priestess = clone_object(
            "/d/Earthsea/gont/tenalders/npc/kargess_axe"
        );
        priestess->move(to);
    }

    for(i = 0; i < 2; i++)
    {
        if(!guards[i])
        {
            guards[i] = clone_object(
                "/d/Earthsea/gont/tenalders/npc/eunuch"
            );
            guards[i]->move(to);
        }

        priestess->team_join(guards[i]);
    }
}

public void
create_room()
{
    set_short("Top of the watch tower");
    set_long("This is the top of the watch tower, a circular room " +
        "surrounded by stone walls with large openings allowing " +
        "a spectacular view of the surroundings. The remains " +
        "of a wooden table lie near the center of the room, " +
        "apparently smashed to bits by a very large axe.\n");
    add_item(({"top", "tower", "watch tower", "room"}),
        "This is the top of a tall watch tower.\n");
    add_item(({"wall", "walls", "stone wall", "stone walls"}),
        "The tower walls are made of sturdy stone and appear " +
        "to be in excellent condition.\n");
    add_item(({"opening", "openings", "large opening",
        "large openings", "window", "windows"}),
        "The walls are covered with several large openings " +
        "providing an excellent view of the surroundings.\n");
    add_item(({"view", "spectactular view", "surroundings",
        "spectactular view of the surroundings",
        "view of the surroundings"}),
        "The tower's location above the cliffs provides an " +
        "excellent view of the city of Gont, though it is " +
        "immediately noticeable that the tower provides " +
        "no view of the cliffside it is built upon.\n");
    add_item(({"remains", "table", "wooden table", "table remains",
        "remains of a table", "remains of a wooden table",
        "wood table", "wood", "ground", "center"}),
        "The smashed remains of a wooden table are piled " +
        "on the ground near the center of the room, cut to " +
        "tiny pieces by a large axe.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower3",
        "down");
    reset_room();
}
