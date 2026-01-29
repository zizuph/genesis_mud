/*
 *   The storage room of the Telberin Jeweler's Shop
 *
 *   Modified from /d/Gondor/minas/rooms/jewel_store.c
 *
 *   Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define GEM_TYPES       ({ ("quartz"),\
                           ("agate"),\
                           ("jasper"),\
                           ("coral"),\
                           ("turquoise"),\
                           ("amber"),\
                           ("onyx"),\
                           ("carnelian"),\
                           ("garnet"),\
                           ("amethyst"),\
                           ("aquamarine"),\
                           ("jade"),\
                           ("lapis"),\
                           ("opal"),\
                        })

#define GEM_DIR 	"/d/Genesis/gems/obj/"

/* prototype */
void reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_emerald_room() 
{
   set_short("The store room of the Jeweller's Shop in Telberin");
   set_long("This is the store room of the Jeweller's Shop in Telberin.\n");

   add_exit("/d/Emerald/telberin/mercantile/jeweler_shop", "south",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   reset_room();
}

void
reset_room()
{
    int     i;
    object  gem;

    for (i = 0; i < sizeof(GEM_TYPES); i++)
    {
        if (!present(GEM_TYPES[i], TO))
        {
            gem = clone_object(GEM_DIR + GEM_TYPES[i]);
            gem->set_heap_size(random(5) + 1);
            gem->move(TO);
        }
    }
}


