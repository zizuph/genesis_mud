/**********************************************************************
 * - coffee.c                                                       - *
 * -                                                                - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("coffee");
    add_name(({"cup"}));
    set_pname("coffees");
    set_adj(({"piping", "hot", "cup"}));
    set_short("piping hot cup of coffee");
    set_pshort("piping hot cups of coffee");
    set_long("This is a nice piping hot cup of coffee.\n");
    set_soft_amount(65);
    add_prop(HEAP_I_UNIT_VOLUME, 50);
    add_prop(HEAP_I_UNIT_VALUE, 45);
 }
 