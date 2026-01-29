/*
 *   The storage room of the Minas Tirith jeweller's shop
 *
 *   Revisions: 7 Feb. 2000 by Stern: Change to Genesis gem system.
 */
inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define GEM_TYPES	({ "amber", "jade", "garnet", \
                           "tourmaline", "turquoise", "emerald", \
                           "opal", "topaz", "sapphire", \
                           "ruby", "diamond" })

#define JEWELSTORE      "/d/Gondor/minas/rooms/jewel_shop"
#define GEM_DIR 	"/d/Genesis/gems/obj/"

/* prototype */
void reset_room();

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

void
create_room() 
{
   set_short("The store room of the Jeweller's Shop in Minas Tirith");
   set_long("This is the store room of the Jeweller's Shop in Minas Tirith.\n");

   add_exit(JEWELSTORE, "south",0);

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

