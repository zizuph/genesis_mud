/**********************************************************************
 * - clams.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("clam");
    add_name(({"clams", "basket"}));
    set_pname("clams");   
    set_adj(({"basket", "fried"}));
    set_short("basket of fried clams");
    set_pshort("baskets of fried clams");
    set_long("This small basket is filled with batter fried clams. "+
      "The clams are fresh and are piping hot with a soft spice "+
      "added to the batter making them delightly to eat.\n");
    set_amount(100);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 200);
}
