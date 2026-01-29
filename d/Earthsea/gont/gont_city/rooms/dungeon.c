#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    set_short("The local dungeon");
    set_long("This building is made from dark granite, "+
        "as strong and impermeable as the city walls. It looks like it "+
        "might be impossible for someone to break through those dark "+
        "walls. There is little light here, from small windows with thick "+
        "iron bars.\n");
    add_item((({"windows", "small windows"})), "The small windows are "+
        "barred with iron, making escape almost impossible.\n");
    add_item((({"floor", "ceiling", "walls", "stone",
        "flagstones", "granite flagstones", "black stone"})),
        "The walls, floor and ceiling are all constructed from the "+
        "same dark stone as the city walls. The large blocks are fitted "+
        "together without mortar.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("jailhouse", "south");
}
