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

public void
create_room()
{
    set_short("a sheltered path in the northeast of "+CASTLE_NAME);
    set_long("You are at the southern reaches of a " +
        "narrow path in the northwest parts of " +
        CASTLE_NAME+". It stretches northwards through the " +
        "narrow space between the outer wall of the " +
        "castle, and the stone foundation of the " +
        "upper levels. Just to the south of here, you " +
        "can see a simple opening cut into the " +
        "stone, a passage that extends beneath the " +
        "surface of the castle. The ground here is " +
        "quite grassy, and soft to walk on. The only " +
        "obstacles to step over are the occasional " +
        "chunks of stone that have fallen from the " +
        "battlements.\n\n");

    add_item(({"sky", "mist"}),
        "High above you, the sky is obscured by a thick " +
        "layer of churning white mist.\n");
    add_item(({"ground", "floor"}),
        "The ground of the path is covered in thick grass, " +
        "making walking quite easy, so long as you don't " +
        "trip over any of the chunks of stone littering " +
        "the surface.\n");
    add_item(({"walls"}),
        "Massive walls of grey stone blocks rise on either " +
        "side of you. Both appear to have suffered a fair " +
        "amount of damage over the years, with gaping " +
        "cracks and holes where stone has crumbled or " +
        "fallen away completely.\n");
    add_item(({"chunks","stone","chunks of stone"}),
        "Scattered across the ground of the path, large " +
        "chunks of stone that have fallen from the walls " +
        "pose the threat of stubbing your toe.\n");
    add_item(({"cracks", "holes"}),
        "The walls are covered with deep cracks and holes " +
        "where stone has crumbled away or even fallen out " +
        "of them.\n");

    add_exit(RUIN + "nw_path_2", "north");
    add_exit(RUIN + "w_tunnel_3", "south");

    reset_room();
}
