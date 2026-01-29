/*********************************************************************
 * - rum.c                                                         - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("rum");
    add_name(({"mug", "buttered"}));
    set_adj(({"mug", "buttered"}));
    set_short("mug of hot buttered rum");
    set_pshort("mugs of hot bettered rum");
    set_long("This is a mug of hot buttered rum.\n");

    set_soft_amount(200);
    set_alco_amount(15);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 200);
}
