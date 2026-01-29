#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define TORCH "/d/Earthsea/gont/gont_city/obj/tower_torch"

private object torch;

public void
reset_room()
{
    torch->reset_torch();
    torch->light_me();
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Dark hallway (third floor)");
    set_long("You find yourself in a dark "+
        "hallway on the third floor of the tower. "+
        "The walls are made of black stone "+
        "carefully fitted together without mortar. The dark "+
        "passage is paved with granite flagstones. Along the "+
        "walls at intervals there are torches set in sconces.\n");
    add_item((({"stone", "black stone", "walls", "floor",
        "granite flagstones", "flagstones"})),
        "The walls and floor are made of the same dark rock as "+
        "the city walls, fitted together without mortar.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_exit("tower_wall", "north");
    add_exit("tower_hall2", "south");
    torch = clone_object(TORCH);
    torch->move(this_object(), 1);
    reset_room();
}
