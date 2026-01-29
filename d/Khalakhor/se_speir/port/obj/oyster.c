/**********************************************************************
 * - oyster.c                                                       - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("oyster");
    set_pname("oysters");
    set_adj(({"fried"}));
    set_short("fried oyster");
    set_pshort("fried oysters");
    set_long("This is a freshly shelled oyster that has been batter "+
      "dipped then fried to perfection.\n");
    set_amount(25);
    add_prop(HEAP_I_UNIT_VOLUME, 25);
    add_prop(HEAP_I_UNIT_VALUE, 85);
}
