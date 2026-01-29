#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
reset_room()
{
    int i,
        num;

    ::reset_room();

    num = sizeof(filter(all_inventory(), &->id(RUBBLE_NAME)));    
    num -= 4;

    setuid();
    seteuid(getuid());

    while (num < 0)
    {
        num ++;
        if (!random(2))
            clone_object(OBJ + "large_rubble")->move(TO);
        else
            clone_object(OBJ + "small_rubble")->move(TO);
        tell_room(TO, "A piece of rubble falls from the " +
            "ceiling.\n");
    }
}

void
create_room()
{
    set_short("inside a ruined building in " + CASTLE_NAME);
    set_long("Whatever this room might once have been, there's " +
        "little left of it now. Everything has caved in, and there's " +
        "only enough room here for a handful of people to stand " +
        "near the entrance to the east. What was once most of the " +
        "ceiling and walls here now lies piled high on the floor " +
        "in cracked and dusty rubble, completely obliterating " +
        "anything that might have been on the other side.\n\n");

    add_item(({"ceiling", "roof"}),
        "What was once the ceiling now lies in a pile on the floor, " +
        "mixed in with a great majority of the walls, it seems.\n");
    add_item(({"walls"}),
        "What were once the walls of this room now lies in a pile " +
        "on the floor, mixed in with the ceiling.\n");
    add_item(({"south wall"}),
        "A small, arched exit leads southwards into a darkened " +
        "tunnel though the south wall.\n");
    add_item(({"floor", "ground", "dust", "debris"}),
        "The ground is quite ordinary, grey stone covered in " +
        "a layer of dust and debris that has fallen from the " +
        "ceiling and walls, over the years.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "build2-build3", "east");

    reset_room();
}
