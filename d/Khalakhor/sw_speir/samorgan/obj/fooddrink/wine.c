/**********************************************************************
 * - wine.c                                                         - *
 * -                                                                - *
 * - Created by Tapakah, 07/2021                                    - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink ()
{
  set_name("wine");
  set_pname("wines");
  set_adj(({"red"}));
  set_short("glass of crimson red wine");
  set_pshort("glasses of crimson red wines");
  set_long("This glass is filled with crimson red wine. The wine "+
           "reflects the light like a ruby would. It smells of "+
           "conifers and forest berries.\n");
  set_soft_amount(85);
  set_alco_amount(45);
  add_prop(HEAP_I_UNIT_VOLUME, 50);
  add_prop(HEAP_I_UNIT_VALUE, 275);
}
