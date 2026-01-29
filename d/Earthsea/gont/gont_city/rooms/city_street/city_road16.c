#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include "city_tells.h"

private object *sailors = allocate(3);

public void
reset_room()
{
    int i = random(3);

    while(i--)
    {
        if(!objectp(sailors[i]))
        {
            sailors[i] = clone_object("/d/Earthsea/gont/gont_city/liv/sailor" + (random(5)+1));
            sailors[i]->move(this_object());
            sailors[i]->command("emote swaggers in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    int i;

    for(i = 0; i < 2; i++) {
        add_tell(HARBOUR_TELLS[random(sizeof(HARBOUR_TELLS))]);
    }

    set_tell_time(120);
    set_short("Northwest part of the harbour");
    set_long("This is the northwest part of the harbour"+
        " where numerous smaller crafts are pulled up on a strip"+
        " of sandy beach between the road and the water."+
        " Looking around you can see many larger ships"+
        " anchored by the three major piers and to the"+
        " southeast the narrow entrance to the bay between"+
        " two steep cliffs. On the other side of the street"+
        " are wooden buildings, probably warehouses."+
        " This part of the harbour is busy with"+
        " fishermen working on their boats and hauling"+
        " their catch ashore.\n");
    add_item("beach","A narrow strip of beach is left"+
        " between the street following the water's edge"+
        " and the bay. Many smaller fishing boats are"+
        " pulled up on it, side by side, and you can"+
        " see fishermen working with repairing them or"+
        " hauling catch ashore.\n");
    add_item(({"road","street"}),"The cobbled street"+
        " follows the quay side to the east and southwest"+
        " here, and is very busy with fishermen, sailors"+
        " and harbour workers, all doing their jobs.\n");
    add_item("piers","Looking out over the bay you"+
        " can see the three major piers stretching out"+
        " into the grey water from the east, south and"+
        " north. Numerous larger ships from all over the"+
        " Archipelago are anchored by them, giving the"+
        " impression of a forest of masts.\n");
    add_item("entrance","A narrow canal between the"+
        " two steep cliffs is the only entrance to this"+
        " secluded harbour.\n");
    add_item("cliffs","Two steep cliffs guard the"+
        " entrance to the harbour, with towers built"+
        " on the tops. These are the famed Armed Cliffs,"+
        " protecting Gont Port from the sea.\n");
    add_item("fishermen","Many fishermen work by the"+
        " water, repairing their boats or nets or just"+
        " hauling a large catch of silvery fish ashore.\n");
    add_exit("city_road17", "east");
    add_exit("city_road10", "southwest");
    add_exit("../warehouse2", "northwest");
    reset_room();
}
