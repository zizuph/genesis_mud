/* 
 * Bucket to hold honeycomb for quest
 * Based on bucket from Gont
 * -- Finwe, December 2005
 */

#pragma strict_types

inherit "/std/container";
inherit "/lib/keep";

#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>

public void
create_container()
{
    set_name("bucket");
    add_name("_sparkle_honey_bucket");
    set_pname("buckets");
    set_adj("wooden");
    set_adj("round");
    set_short("round wooden bucket");
    set_pshort("round wooden buckets");
    set_long("This is a round wooden bucket. It looks well used and " +
        "designed to hold honeycomb.\n");

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 100);
    set_keep(1);
}

public int
query_bucket_full()
{
    int honeycomb = 0;
    object *inv;
    int i = 0;

    inv = all_inventory(this_object());

    for(i = 0; i < sizeof(inv); i++)
    {
        if (inv[i]->id ("honeycomb"))
        {
            honeycomb++;
        }
    }

    return (honeycomb >= MAX_HONEY);
}

