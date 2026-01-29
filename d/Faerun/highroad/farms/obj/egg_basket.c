/* 
 * Basket for egg gathering quest
 * Based on bucket from Gont
 * -- Finwe, December 2005
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>

inherit "/std/container";
inherit "/lib/keep";
//inherit "/std/heap";
#define MAX_EGGS_BASKET 12

public void
create_container()
{
    set_name("basket");
    add_name("_faerun_egg_basket");
    set_pname("baskets");
    set_adj("wooden");
    set_adj("oval");
    set_short("oval wooden basket");
    set_pshort("oval wooden baskets");
    set_long("This is an oval wooden basket. It is lightweight and designed " +
        "to hold chicken eggs.\n");

    add_prop(OBJ_M_NO_SELL,1);  // quest item. unsellable
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 0);
    set_keep(1);
}

public int
query_bucket_full()
{
    int eggs = 0;
    object *inv;
    int sz, i = 0;

    inv = all_inventory(this_object());

//    for(i = 0, sz = sizeof(inv); i < sz; i++)
    for(i = 0; i < sizeof(inv); i++)
    {
        if (inv[i]->id("_chicken_egg"))
        {
            eggs++;
        }
    }
    return (eggs >= MAX_EGGS_BASKET);
}

public void
enter_inv(object obj, object from)
{
    int i = 0, sz;
    object *inv, eggshell;

    seteuid(getuid(TO));

    ::enter_inv(obj, from);
    if (!living(from))
	    return;

/*    if (!obj->id("_chicken_egg")) 
    {
        write("Oh no! The eggs in the basket have been broken!!!\n");

        inv = all_inventory(this_object());
        for(i = 0; i < sizeof(inv); i++)
    
        {
            if (inv[i]->id("_chicken_egg"))
                inv[i]->remove_object();
            eggshell = clone_object(FOBJ_DIR + "eggshell");
            eggshell->move(TO);
        }
    }*/

    if (!obj->id("_chicken_egg")) 
    {

        inv = all_inventory(this_object());
        for(i = 0; i < sizeof(inv); i++)
    
        {
            if (inv[i]->id("_chicken_egg"))
            {
                sz++;
                inv[i]->remove_object();
                eggshell = clone_object(FOBJ_DIR + "eggshell");
                eggshell->move(TO);
            }
        }
        if (sz) 
            write("Oh no! The eggs in the basket have been broken!!!\n");

    }


}
