/*********************************************************************
 * - cider.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("cider");
    add_name(({"hot", "mug"}));
    set_adj(({"mug", "hot"}));
    set_short("mug of hot cider");
    set_pshort("mugs of hot cider");
    set_long("This is a mug of hot cider.\n");

    set_soft_amount(200);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 100);
}
