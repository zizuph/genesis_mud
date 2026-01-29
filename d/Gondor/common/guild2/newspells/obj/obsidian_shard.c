/*
 *    /d/Gondor/common/guild2/newspells/obj/obsidian_shard.c
 *
 *    The shard symbolizes something very sharp to cut with
 *    and works as ingredient in the morgul spell 
 *    Orekir - Heart Cleave
 *
 *    Toby, 27-Sept-2007
 */
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_object()
{
    set_name( ({ "shard", "orekir_ingr1" }) );
    set_pname("shards");
    set_short( "small obsidian shard" );
    set_pshort( "small obsidian shards" );
    set_adj( ({ "small", "obsidian" }) );
    set_long( "You gaze upon a small obsidian shard, its " +
              "surface faded and riddled with cracks. The " +
              "cutting edges, however, are of deepest black.\n" );
    
    add_prop( OBJ_I_VALUE, 2);
    add_prop( OBJ_I_WEIGHT, 3);
    add_prop( OBJ_I_VOLUME,  3);
}

public void remove_object()
{
    tell_room( environment( this_object() ),
        "The small obsidian shard crumbles to dust " +
        "which spread before you in a sudden gust of wind.\n");
    ::remove_object();
}
