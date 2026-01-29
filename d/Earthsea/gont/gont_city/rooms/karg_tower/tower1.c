/* 2017-11-06 Malus: Changed check_guard() to use present() */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

private object *guards = allocate(3);

public void
reset_room()
{
    int i;

    for(i = 0; i < 3; i++)
    {
        if(guards[i])
        {
            continue;
        }

        guards[i] = clone_object(
            "/d/Earthsea/gont/tenalders/npc/karg" + (random(3) + 2)
        );
        guards[i]->move(this_object());

        if(i > 0)
        {
            guards[0]->team_join(guards[i]);
        }
    }

}

public void
create_room()
{
    set_short("First floor of the watch tower");
    set_long("Blood stains and bits of tattered wood strewn " +
        "across the floor mark the entryway into this tall " +
        "tower, once used by the Lord of Gont's mercenary " +
        "army to keep watch over the city. A stairway in " +
        "the southeast corner leads up the tower.\n");
    add_item(({"stain", "stains", "blood", "blood stain",
        "blood stains"}),
        "Fresh blood stains.\n");
    add_item(({"wood", "tattered wood", "bits", "bit",
        "bits of wood", "bit of wood", "bit of tattered wood",
        "bits of tattered wood"}),
        "Bits of wood lie strewn about the floor, apparently " +
        "from the doors that once stood in the entryway.\n");
    add_item("floor", "The floor is covered with blood " +
        "and bits of wood.\n");
    add_item(({"tower", "tall tower"}), "The watch tower " +
        "was built to keep guard over the city and the vital " +
        "port traffic.\n");
    add_item(({"stair", "stairs", "winding stairs", "stairway",
        "winding stairway", "southeast corner", "corner",
        "stairway in the southeast corner",
        "stairway in the corner"}),
        "The winding stairs lead up into the watch tower.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower2",
        "up", "@@check_guards");
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/cliff1",
        "out");
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
            write("An unpleasant looking kargish guard blocks you " +
                "as you approach the stairs.\n");
            return 1;
        }
    }

    return 0;
}
