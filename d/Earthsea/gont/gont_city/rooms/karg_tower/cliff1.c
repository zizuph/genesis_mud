/* 2017-11-06 Malus: Changed check_guard() to use present() */ 
#pragma strict_types

inherit "/std/room";
inherit "/d/Earthsea/gont/gont_city/rooms/tower_climb";

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
            "/d/Earthsea/gont/tenalders/npc/karg" + (random(3) + 1)
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
    set_short("Atop a cliff by Gont Port");
    set_long("You stand upon the top of a cliff overlooking " +
        "the port city of Gont. Just south of you lies the entrance " +
        "to a tall stone watch tower. The tower seems to rise at least " +
        "three levels above ground and by its location, it seems " +
        "to be very important to defence of the port city. The entryway " +
        "to the tower lies open and unprotected.\n");
    add_item(({"top", "cliff", "top of the cliff",
        "view", "overlook", "gont", "port city of gont",
        "port", "city"}),
        "This is the top of a cliff overlooking the port " +
        "of Gont.\n");
    add_item(({"tower", "watch tower", "stone tower", "tall tower",
        "tall stone tower", "tall watch tower", "stone watch tower",
        "tall stone watch tower"}),
        "A tall stone watch tower built of roughly cut grey stone " +
        "stands to the south, clearly erected to guard the port.\n");
    add_item(({"stone", "grey stone", "rough stone", "roughly cut stone",
        "rough grey stone", "roughly cut grey stone"}),
        "The tower watch tower is built of roughly cut grey stone.\n");
    add_item(({"door", "doors", "entry", "entryway",
        "entryway to the tower"}),
        "Upon closer inspection it seems that the entryway " +
        "was once covered by wooden doors, but they have recently " +
        "been knocked down by brute force.\n");
    add_exit("/d/Earthsea/gont/gont_city/rooms/karg_tower/tower1",
        "south", "@@check_guards");
    set_next_up("on_top");
    set_next_down("/d/Earthsea/gont/gont_city/rooms/city_street/city_road23a");
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
            write("A kargish guard steps in front of you and " +
                "blocks your way into the tower.\n");
            return 1;
        }
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
