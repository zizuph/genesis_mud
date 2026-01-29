/*********************************************************************
 * - pheasant.c                                                    - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("pheasant");
    set_adj(({"roasted"}));
    set_short("slice of roasted pheasant");
    set_pshort("slices of roasted pheasant");
    set_long("This is a tender piece of roasted pheasant.\n");
    set_amount(100);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 100);
}
