/**********************************************************************
 * - bmilk.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("buttermilk");
    add_name("milk");
    add_adj(({"cup"}));
    set_short("cup of buttermilk");
    set_pshort("cups of buttermilk");
    set_long("This is a nice cup of buttermilk that is a "+
      "frequent drink of citizens of SaMorgan.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 55);
    add_prop(HEAP_I_UNIT_VALUE, 75);
 }