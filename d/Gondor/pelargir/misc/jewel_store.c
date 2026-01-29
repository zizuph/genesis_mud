/*
 *   The storage room of the Pelargir jeweller's shop
 *
 */
inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define JEWELSTORE      "/d/Gondor/pelargir/misc/jewel_shop"
#define GEM_TYPES	({ "amber", "amethyst", "carnelian",  \
                           "emerald", "lapis", "moonstone",   \
                           "onyx", "opal", "peridot", "ruby", \
                           "sapphire", "topaz_yellow",        \
                           "tourmaline" })

#define GEM_DIR 	"/d/Genesis/gems/obj/"

public void
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

public void
create_room() 
{
    set_short("Rindul's storage room");
    set_long("This is the store room of the Jeweller's Shop in Pelargir.\n");
    add_exit(JEWELSTORE, "north",0);
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("_gondor_silver_dust") ||
      ob->id("_gondor_gold_dust"))
    {
        set_alarm(0.9, 0.0, &tell_room(JEWELSTORE, "A small " +
            "boy enters at the " +
            "shopkeeper's call. He takes the " + ob->short() +
            ", stuffs it in a hidden pocket, and runs off " +
            "to deliver it to a waiting customer.\n"));
        set_alarm(1.0, 0.0, &ob->remove_object());
    }
    else
    {
        store_update(ob);
    }
}
