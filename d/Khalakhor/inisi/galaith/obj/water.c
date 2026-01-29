/*********************************************************************
 * - water.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("water");
    add_name(({"glass", "cool water"}));
    set_adj(({"glass", "cool"}));
    set_short("glass of cool water");
    set_pshort("glasses of cool water");
    set_long("This is a glass of cool water.\n");

    set_soft_amount(200);
    set_alco_amount(0);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 20);
}
