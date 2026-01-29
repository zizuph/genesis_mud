#pragma save_binary
#pragma strict_types

#include "../defs.h"
inherit "/d/Cirath/std/room.c";
inherit "/lib/store_support";

#define SHOP ALT_HOU + "boot_shop"

void
reset_room()
{
    object ob;

    if (!present("torch", this_object()))
    {
        ob = clone_object(ALT_ARM + "simple_lth_boots.c");
        ob->move(TO);
    }
}

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(SHOP, "west");

    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
