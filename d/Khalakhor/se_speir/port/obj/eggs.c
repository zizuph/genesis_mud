/*********************************************************************
 * - eggs.c                                                        - *
 * - Scrammbled eggs                                               - *
 * - Created by Damaris 02/2005                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("eggs");
    set_adj(({"scrambled"}));
    set_short("bowl of scrambled eggs");
    set_pshort("bowls of scrambled eggs");
    set_long("This is a bowl of scrambled eggs.\n");
    set_amount(80);
    add_prop(HEAP_I_UNIT_VOLUME, 50);
    add_prop(HEAP_I_UNIT_VALUE, 30);
}
