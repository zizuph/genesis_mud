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
            "/d/Earthsea/gont/tenalders/npc/karg6"
        );
        guards[i]->move(this_object());

    }

    guards[1]->team_join(guards[0]);
}

public void
create_room()
{
    set_short("Stairway on the second floor of the watch tower");
    set_long("This small corridor provides a short break from " +
        "the winding stairs leading up and down the tower. A door " +
        "lies shattered in the eastern wall, looking too dangerous " +
        "to pass.\n");
    add_item(({"stair", "stairs", "winding stairs", "stairway",
        "winding stairway"}),
        "The winding stairs lead up and down the watch tower.\n");
    add_item(({"corridor", "small corridor", "room"}),
        "This corridor provides a short break from the monotony " +
        "of the winding stairs.\n");
    add_item(({"door", "eastern wall", "east wall", "wall",
        "shattered door", "eastern door", "east door"}),
        "The shattered remains of the door in the eastern wall " +
        "look too dangerous to pass through until someone more " +
        "daring (or stupid) than you attempts to clear the way.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower3",
        "up", "@@check_guards");
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower1",
        "down");
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/storeroom",
        "east", "@@shattered_door");
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
            write("A fierce looking kargish guard blocks you " +
                "as you approach the stairs.\n");
            return 1;
        }
    }

    return 0;
}

public int
shattered_door()
{
    write("The shattered doorway looks too dangerous to pass through.\n");
    return 1;
}
