/*********************************************************************
 * - cocoa.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("cocoa");
    add_name(({"mug"}));
    set_adj(({"piping", "hot"}));
    set_short("mug of piping hot cocoa");
    set_pshort("mugs of piping hot cocoa");
    set_long("This is a mug of piping hot cocoa with tiny little "+
      "marshmallows floating on top..\n");

    set_soft_amount(200);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 100);
}
