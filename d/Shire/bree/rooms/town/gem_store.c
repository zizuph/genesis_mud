/*
 *   The storage room of the Bree gemshop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include </sys/stdproperties.h>

#define GEM_TYPES	({ "amber", "amethyst", "carnelian",  \
                           "emerald", "lapis", "moonstone",   \
                           "onyx", "opal", "peridot", "ruby", \
                           "sapphire", "topaz_yellow",        \
                           "tourmaline" })

#define GEM_DIR 	"/d/Genesis/gems/obj/"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
    set_short("Gem Storage Room");
    set_long("This is the jewelry storage room of the Gem Shop.\n");

    set_max_values(100, 7);

    add_exit(TOWN_DIR + "gem_shop","south");

    add_prop(ROOM_I_NO_CLEANUP, 1); // We don't want this room to be unloaded
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}

reset_room() 
{
    int index;
    object gem;

    for (index = 0; index < sizeof(GEM_TYPES); index++)
    {
        if (!present(GEM_TYPES[index], this_object()))
        {
            gem = clone_object(GEM_DIR + GEM_TYPES[index]);
            gem->set_heap_size(random(5) + 1);
            gem->move(this_object());
        }
    }
}
