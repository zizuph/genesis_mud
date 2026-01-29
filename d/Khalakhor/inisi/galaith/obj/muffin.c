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
    set_name("muffin");
    set_adj(({"hot", "apple"}));
    set_short("hot apple muffin");
    set_pshort("hot apple muffins");
    set_long("It is hot with melting butter dripping down its "+
      "soft flaking sides.\n" +
      "It looks very sweet and tasty.\n");
    set_amount(80);
    add_prop(HEAP_I_UNIT_VOLUME, 30);
    add_prop(HEAP_I_UNIT_VALUE, 80);
}
