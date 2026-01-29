/**********************************************************************
 * - corncakes.c                                                    - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("corncake");
    set_adj(({"piping", "hot"}));
    set_short("piping hot corncake");
    set_pshort("piping hot corncakes");
    set_long("This is a piping hot corncake that is served with "+
      "meals as a side bread or as a breakfast cake.\n");
    set_amount(100);
    add_prop(HEAP_I_UNIT_VOLUME, 80);
    add_prop(HEAP_I_UNIT_VALUE, 40);
}
