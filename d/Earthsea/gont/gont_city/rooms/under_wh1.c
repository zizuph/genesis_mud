#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

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
    set_short("Tunnel beneath the city");
    set_long("Amazingly enough this tunnel has been " +
        "plowed through deep rock and mud beneath the " +
        "streets of Gont. A sturdy wooden frame supports " +
        "the tunnel and forms a ladder that leads up " +
        "towards a small covered passage high above the " +
        "floor.\n");
    add_item(({"deep rock", "rock", "mud"}),
        "This tunnel has been carved out of the " +
        "thick mud and rock that support the great " +
        "city of Gont.\n");
    add_item(({"frame", "wooden frame", "wood frame",
        "sturdy wooden frame", "sturdy wood frame",
        "support", "supports", "beams", "support beams",
        "beam", "support beam", "ladder"}),
        "An intricate network of wooden beams has " +
        "been constructed to support the tremendous " +
        "weight of the earth surrounding the tunnel.\n");
    add_item("floor", "The very earth itself.\n");
    add_item("wood", "Wood. It looks sturdy.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Earthsea/gont/gont_city/rooms/warehouse4",
        "up", "@@ladder_msg");
    add_exit("/d/Earthsea/gont/gont_city/rooms/under_wh2",
        "northwest");
    reset_room();
}

public int
ladder_message()
{
    write("You carefully climb your way up the support " +
        "beams and push open the passageway.\n");
    return 0;
}
