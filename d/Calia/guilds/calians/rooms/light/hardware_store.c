/* 
 * Coders : Mercade and Maniac 
 * 
 * This is the store-room of the hardware shop of the 
 * crystalline palace.  Adapted from the original code 
 * by Mercade for the dwarven race guild store. 
 * 
 * Created 2/2/94 by Maniac 
 * 
 * Revision history: 
 *    3/2/2001  updated directory refs                       Maniac 
 *    9/2/97    changed argos references to new argos        Zima 
 *    14/9/96   added an extra rope for the mermaid quest    Jaacar 
 *    26/3/96   lamps and flasks imported from Argos         Maniac 
 *    25/3/96   backpacks updated                            Maniac 
 *    24/2/96   garden quest items added                     Maniac 
 *     6/6/95   Bug corrected                                Maniac 
 *     22/5/95  Fine cloth added to store                    Maniac 
 *     12/9/95  Chisel added to store (for polymorph quest)  Maniac 
 */ 

#pragma save_binary

inherit "/lib/store_support";
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

#define CLONE_OBJECT(s) clone_object(s)->move(this_object())

/*
 * This define defines the standard inventory that should be cloned every
 * reset if the shop is not in full stock. The first entry is the function
 * that is used to create the object, the second its filename and the third
 * is the number of objects that should be in stock.
 */
#define MINIMUM_INVENTORY                      \
 ({ ({ "create_torch", "/d/Calia/argos/metro/objects/oil_lamp",4}),\
    ({ "create_object", "/d/Calia/argos/metro/objects/oilflask",6}), \
    ({ "create_rope",  CRPALACE_OBJECTS + "rope", 2}),\
    ({ "create_object", "/d/Calia/mountain/obj/chisel", 2}),\
    ({ "create_pack", CRPALACE_OBJECTS + "sack",4}),\
    ({ "create_pack", CRPALACE_OBJECTS + "backpack",6}),\
    ({ "create_object", "/d/Calia/mountain/obj/fine_cloth", 1 }), \
    ({ "create_object", "/d/Calia/mountain/obj/trowel", 1 }), \
    ({ "create_object", "/d/Calia/mountain/obj/watering_can", 1 }) \
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
    int    i, j, k;
    int    num_found;

    for (i = 0; i < sizeof(to_check); i++)
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
    set_short("The store-room of the hardware shop");
    set_long("This store-room is used to store all items that are for " +
        "sale in the hardware shop in the crystalline palace." +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);

    set_alarm(1.0, 0.0, reset_room);
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

