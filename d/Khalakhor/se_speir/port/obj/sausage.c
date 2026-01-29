/**********************************************************************
 * - sausage.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("sausage");
    set_pname("sausages");
    set_adj(({"spicy", "hot"}));
    set_short("piece of spicy hot sausage");
    set_pshort("pieces of spicy hot sausages");
    set_long("This piece of sausage is very spicy hot being made "+
      "with special ground red and green peppers that have been "+
      "ground into the meat before it was prepared. It make a nice "+
      "adition to any meal needing a bit of jest.\n");
    set_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 50);
    add_prop(HEAP_I_UNIT_VALUE, 30);
}
