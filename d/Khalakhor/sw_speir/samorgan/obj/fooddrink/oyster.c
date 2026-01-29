/**********************************************************************
 * - oyster.c                                                       - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/food";

void
create_food ()
{
  set_name("oyster");
  set_pname("oysters");
  set_adj(({"large", "fried"}));
  set_short("large fried oyster");
  set_pshort("large fried oysters");
  set_long("This is a large freshly shelled oyster that has been "+
           "batter dipped then fried to perfection.\n");
  set_amount(55);
  add_prop(HEAP_I_UNIT_VOLUME, 55);
  add_prop(HEAP_I_UNIT_VALUE, 145);
}
