/*
 * /d/Terel/mountains/ghastly_keep/obj/g_tear.c
 *
 * Ghastly tear 
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 * 2020-12-11 - Cotillion
 * - Made tears heaps
 */

inherit "/std/heap";
#include "../defs.h";

#include <stdproperties.h>
#include <macros.h>

void
create_heap()
{
    set_heap_size(1);

    set_name("tear");
    add_name("_ghastly_keep_tear");
    set_adj("ghastly");
    add_adj("tear");

    set_short("ghastly tear");
    set_long("A droplet shaped as a tear, made out of sticky material.\n");

    add_prop(HEAP_I_UNIT_VALUE, 415);
    add_prop(HEAP_I_UNIT_WEIGHT, 10);
    add_prop(HEAP_I_UNIT_VOLUME, 10);

    add_prop(HEAP_S_UNIQUE_ID, "_terel_ghastly_tear");
}
