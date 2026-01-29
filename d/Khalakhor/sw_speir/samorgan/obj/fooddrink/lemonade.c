/**********************************************************************
 * - lemonade.c                                                     - *
 * -                                                                - *
 * - Created by Tapakah, 07/2021                                    - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink ()
{
  set_name("lemonade");
  set_pname("lemonades");
  add_adj(({"red"}));
  set_short("mug of red lemonade");
  set_pshort("mugs of red lemonades");
  set_long("This is a mug of red lemonade, the favorite drink of the "+
           "children of SaMorgan.\n");
  set_soft_amount(45);
  add_prop(HEAP_I_UNIT_VOLUME, 55);
  add_prop(HEAP_I_UNIT_VALUE, 75);
}
