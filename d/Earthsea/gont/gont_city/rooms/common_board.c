#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Earthsea board room");
    set_long("This room is actually little more than "+
        "a closet. It is very bare except for a board that "+
        "covers most of one wall. Soft light filters in so "+
        "that you may read the notes posted on it.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_exit("adv_guild", "back");
    setuid();
    seteuid(getuid());
    clone_object("/d/Genesis/obj/board")->move(this_object(), 1);
}
