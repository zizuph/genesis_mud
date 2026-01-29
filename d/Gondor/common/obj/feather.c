/* 
 * /d/Gondor/common/obj/feather.c
 *
 * A pigeon feather, used as spell ingredient.
 *
 * Taken from /d/Calia/worshippers/objects/feather.c
 * 
 * Olorin, July 1997
 *
 */
#pragma strict_types

inherit "/std/heap.c";

#include <stdproperties.h>

public void
create_heap() 
{
    set_name("feather");
    set_short("white feather");
    set_pshort("white feathers");
    set_long("This is the white feather of a pigeon.\n");
    set_heap_size(1);

    add_prop(HEAP_I_UNIT_WEIGHT, 1);
    add_prop(HEAP_I_UNIT_VOLUME, 5);
    add_prop(HEAP_I_UNIT_VALUE,  0);
    add_prop(HEAP_S_UNIQUE_ID, "feather");
 }

