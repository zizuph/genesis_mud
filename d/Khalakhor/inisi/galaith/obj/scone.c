/*********************************************************************
 * - scone.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("scone");
    add_name(({"pastry", "puff pastry"}));
    set_adj(({"flakey", "cream"}));
    set_short("flakey cream scone");
    set_pshort("flakey cream scones");
    set_long("The scone is cone shaped with a flakey puff pastry "+
      "that has been filled with a sweet cream.\n");
    set_amount(110);
    add_prop(HEAP_I_UNIT_VOLUME, 45);
    add_prop(HEAP_I_UNIT_VALUE, 110);
}
