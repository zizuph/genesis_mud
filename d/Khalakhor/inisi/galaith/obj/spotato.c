/*********************************************************************
 * - potato.c                                                      - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("potato");
    add_name("potatoes");
    set_adj(({"roasted", "sweet"}));
    set_short("bowl of roasted sweet potatoes");
    set_pshort("bowls of roasted sweet potatoes");
    set_long("This is a small bowl of roasted sweet potatoes.\n");
    set_amount(80);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 40);
}
