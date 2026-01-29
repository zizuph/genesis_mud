/*********************************************************************
 * - biscuit.c                                                     - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("biscuit");
    set_adj(({"hot"}));
    set_short("hot buttered biscuit");
    set_pshort("hot buttered biscuits");
    set_long("It is hot with melting butter dripping down its "+
      "soft flaking sides.\n" +
      "It looks very tempting.\n");
    set_amount(80);
    add_prop(HEAP_I_UNIT_VOLUME, 30);
    add_prop(HEAP_I_UNIT_VALUE, 80);
}

