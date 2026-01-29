#pragma strict_types

#include <stdproperties.h><b></b>
inherit "/std/room";

private int num_workers = 1+random(3);
private object *workers = allocate(num_workers);

public void
reset_room()
{
    int i = num_workers;

    while(--i >= 0)
    {
        if(workers[i])
        {
            continue;
        }

        workers[i] = clone_object(
            "/d/Earthsea/gont/gont_city/liv/smuggler_labourer"
        );
        workers[i]->move(this_object());
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("A small landing under the docks");
    set_long("This is a small boat landing hidden away " +
        "beneath the docks of Gont Port. The wooden pier " +
        "extends to the southeast where a tunnel " +
        "has recently been dug into the earth. While it is " +
        "apparent that the dock has been recently constructed, " +
        "perhaps even by cover of night, it seems as though " +
        "the landing was created to support a high volume " +
        "of traffic.\n");
    add_item(({"landing", "boat landing", "small landing",
        "small boat landing", "dock", "docks", "pier",
        "wooden pier"}),
        "A sturdy wooden pier.\n");
    add_item(({"tunnel", "earth", "southeast", "rock"}),
        "Amazing as it seems, a tunnel has been dug through " +
        "hard earth and rock to the southeast.\n");
    add_item("wood", "Wood. It looks sturdy.\n");
    add_exit("/d/Earthsea/gont/gont_city/rooms/under_wh1",
        "southeast");
    reset_room();
}
