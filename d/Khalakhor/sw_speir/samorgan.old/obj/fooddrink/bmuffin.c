/**********************************************************************
 * - bmuffin.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("muffin");
    set_pname("muffins");
    set_adj(({"blueberry"}));
    set_short("blueberry muffin");
    set_pshort("blueberry muffins");
    set_long("This muffin is made with the meal of white corn and fresh "+
      "blueberrie. It has been baked in a stone oven in pan molds that "+
      "are round producing a nice plump blueberry muffin.\n");
    set_amount(60);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 40);
}
