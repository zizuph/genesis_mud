/**********************************************************************
 * - eel.c                                                          - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("eel");
    set_pname("eels");
    set_adj(({"plate"}));
    set_short("plate of eel");
    set_pshort("plates of eel");
    set_long("This plate is filled with steaming hot eel that has "+
      "been steamed then quickly fried in butter and spices.\n");
    set_amount(200);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 240);
}
