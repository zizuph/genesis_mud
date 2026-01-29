/* 2017-11-06 Malus: Changed check_guard() to use present() */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

private object *guards = allocate(2);

public void
reset_room()
{
    int i;

    for(i = 0; i < 2; i++)
    {
        if(guards[i])
        {
            continue;
        }

        guards[i] = clone_object(
            "/d/Earthsea/gont/tenalders/npc/eunuch"
        );
        guards[i]->move(this_object());

        if(i == 1)
        {
             guards[i]->team_join(guards[0]);
        }
    }
}

public void
create_room()
{
    set_short("Guard room on the third floor of the watch tower");
    set_long("The walls of this room are lined with wooden " +
        "racks obviously once used to store weapons and " +
        "armours. At the north end of the room lies a " +
        "heavily polished white stone staircase leading up, " +
        "though someone has carelessly tracked mud all over it.\n");
    add_item(({"wall", "walls", "rack", "racks", "wood rack",
        "wood racks", "wooden rack", "wooden racks"}),
        "The walls are covered with wooden racks that were " +
        "used to store equipment before the tower was " +
        "ransacked.\n");
    add_item(({"end", "north end", "end of the room",
        "north end of the room"}),
        "A large staircase lies at the north end of the room.\n");
    add_item(({"stair", "stairs", "staircase", "large stair",
        "large stairs", "large staircase", "stone", "white stone",
        "polished stone", "polished white stone",
        "heavily polished stone", "heavily polished white stone"}),
        "The staircase at the north end of the room is made of " +
        "a white stone that has been carefully polished, though " +
        "someone has recklessly tracked mud all over it.\n");
    add_item("mud", "Someone has tracked mud all over the stairs " +
        "to the north.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower4",
        "up", "@@check_guards");
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower2",
        "down");
    reset_room();
}

public int
check_guards()
{
    int i;

    for(i = 0; i < sizeof(guards); i++)
    {
        if(present(guards[i]))
        {
            write("A eunuch guard blocks you as you approach " +
                "the staircase.\n");
            return 1;
        }
    }

    return 0;
}
