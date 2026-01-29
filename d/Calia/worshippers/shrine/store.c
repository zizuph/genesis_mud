
 /*  A store room for the Shrine Store */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include <files.h>
#include "defs.h"

#define CLONE_OBJECT(s) clone_object(s)->move(this_object())

#define MINIMUM_INVENTORY        \
  ({ ({ "create_weapon", "/d/Calia/sea/weapons/br_trident",3}),\
    ({ "create_weapon", "/d/Calia/sea/weapons/tin_trident",2}),\
    ({ "create_weapon", "/d/Calia/sea/weapons/ori_trident",1}),\
    ({ "create_pack", CALIAN_GUILD_BASE_DIR+"objects/backpack",3}),\
    ({ "create_container", "/d/Genesis/std/potions/mortar",3}), \
    ({ "create_heap", POTION_VIAL_OBJECT,5}), \
     ({ "create_container", "/d/Calia/sea/objects/herbpouch",3}),\
    ({ "create_armour", "/d/Calia/sea/objects/herb_gloves",3})\
 })

mixed to_check = MINIMUM_INVENTORY;

int
object_filter(object obj, string cr, string path)
{
    return (function_exists(cr, obj) == path);
}

void
reset_room()
{
    object *all_inv = all_inventory();
    int i, j;
    int num_found;

    for (i=0; i < sizeof(to_check); i++)
    if ((num_found = sizeof(filter(all_inv, 
              &object_filter(, to_check[i][0], to_check[i][1]) ))) 
                               < to_check[i][2])
    {
        for (j = num_found; j < to_check[i][2]; j++)
            CLONE_OBJECT(to_check[i][1]);
    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("Store Room");
    set_long("This is the store room for the Shrine store.  "+
        "How the hell did you get in here?! Get out! <grin>\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(WOR_SHRINE +"shop", "east", 0, 1);
    reset_room();
}

