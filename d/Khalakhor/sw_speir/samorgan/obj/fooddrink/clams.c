/**********************************************************************
 * - clams.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/food";

void
create_food ()
{
  set_name("clam");
  add_name(({"clams", "plate"}));
  set_pname("clams");   
  set_adj(({"plate", "steamed"}));
  set_short("plate of steamed clams");
  set_pshort("plates of steamed clams");
  set_long("This small plate is filled with plump steamed clams. "+
           "The clams are fresh and are piping hot with a soft red pepper "+
           "spice sprinkled on them making them delightful to eat.\n");
  set_amount(100);
  add_prop(HEAP_I_UNIT_VOLUME, 100);
  add_prop(HEAP_I_UNIT_VALUE, 200);
}
