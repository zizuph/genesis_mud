/**********************************************************************
 * - corncake.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/food";

void
create_food ()
{
  set_name("corncake");
  set_pname("corncakes");
  set_adj(({"piping", "hot"}));
  set_short("piping hot corncake");
  set_pshort("piping hot corncakes");
  set_long("This is a piping hot corncake that was specially prepared "+
           "and is served with meals as a side bread or as a breakfast "+
           "cake.\n");
  set_amount(100);
  add_prop(HEAP_I_UNIT_VOLUME, 80);
  add_prop(HEAP_I_UNIT_VALUE, 40);
}
