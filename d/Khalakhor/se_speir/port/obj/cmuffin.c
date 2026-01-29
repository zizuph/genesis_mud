/**********************************************************************
 * - cmuffin.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("muffin");
    set_pname("muffins");
    set_adj(({"corn"}));
    set_short("corn muffin");
    set_pshort("corn muffins");
    set_long("This muffin is made with the meal of white and yellow "+
      "corn. It has been baked in a stone oven in pan molds that "+
      "resemble ears of corn.\n");
    set_amount(60);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 40);
}
