/*
 * garg_rubble.c
 *
 * The 'corpse' of the guardian gargoyles at the entrance to
 * the black tower. 
 * 
 * Khail - July 7/97
 */
#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{
    set_name("pile");
    set_pname("piles");
    add_name("pile of rubble");
    add_name("rubble");
    add_pname("piles of rubble");
    set_short("pile of rubble");
    set_pshort("piles of rubble");
    set_long("A pile of rubble, little more than crumbled " +
        "stone that looks as if it might once have been a " +
        "statue of some sort.\n");

    add_prop(OBJ_M_NO_GET,"You see little point, the rubble " +
        "is worthless.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT, 200000);
}
