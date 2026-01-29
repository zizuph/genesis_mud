/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village of Rust, and serves as the storeroom for the
general store there. Heavy inspiration from Maniacs shop in
the Crystalline palace */

inherit "/lib/store_support";
inherit "/std/room";

#include <defs.h>
#include <macros.h>
#include <stdproperties.h>

#define CLONE_OBJECT(s) clone_object(s)->move(this_object())

/*
 * This define defines the standard inventory that should be cloned every
 * reset if the shop is not in full stock. The first entry is the function
 * that is used to create the object, the second its filename and the third
 * is the number of objects that should be in stock.
 */
#define MINIMUM_INVENTORY                      \
    ({ ({ "create_torch", "/d/Calia/argos/metro/objects/oil_lamp",2}),\
       ({ "create_object", "/d/Calia/argos/metro/objects/oilflask",4}),\
       ({ "create_pack","/d/Calia/central/rust/objects/light_backpack",3}),\
    })

/*
 * Global variable
 */
mixed to_check = MINIMUM_INVENTORY;

/*
 * extra = ({ function_name, filename }) ... given from reset_room()
 */

int
object_filter(string extra1, string extra2, object obj)
{
    return (function_exists(extra1, obj) == extra2);
}


void
reset_room()
{
    object *all_inv = all_inventory(this_object());
    int    i, j, k, s;
    int    num_found;

    setuid(); seteuid(getuid());
   
    for (i = 0, s = sizeof(to_check); i < s; i++)

        if ((num_found = sizeof(filter(all_inv, 
            &object_filter(to_check[i][0], to_check[i][1]) ))) 
               < to_check[i][2])
        {
            for (j = num_found; j < to_check[i][2]; j++)
                CLONE_OBJECT(to_check[i][1]);
        }
}


void
create_room() 
{
    set_short("Store room for general store");
    set_long("Store room in general store.\n");

    add_prop(ROOM_I_INSIDE, 1);

    set_alarm(1.0, 0.0, reset_room);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
