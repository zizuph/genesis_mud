/**********************************************************************
 * - poitin.c                                                         - *
 * -                                                                - *
 * - Created by Tapakah, 07/2021                                    - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink ()
{
  set_name("poitin");
  set_pname("poitins");
  set_adj(({"clear"}));
  set_short("thimble of clear poitin");
  set_pshort("thimbles of clear poitins");
  set_long("This little thimble is filled with poitin. The poitin "+
           "is the most potent drink ever distilled on the continent. "+
           "It's made from potatoes and its smell is not particularly " +
           "pleasant.\n");
  set_soft_amount(5);
  set_alco_amount(65);
  add_prop(HEAP_I_UNIT_VOLUME, 15);
  add_prop(HEAP_I_UNIT_VALUE, 1728);
}
