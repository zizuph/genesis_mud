/*  /d/Raumdor/common/beach/bountiful/obj/obsidian_shard.c
 *
 *  Crate supply item.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("_obsidian_shard");
    add_name("shard");
    set_adj("obsidian");
    
    set_short("obsidian shard");
    set_pshort("obsidian shards");
    
    set_long("This is a small shard of black volcanic glass, "
    +"measuring about fice inches in lenght and one inch in width.\n");
    
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 10000);
}