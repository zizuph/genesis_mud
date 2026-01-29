/**********************************************************************
 * - bmilk.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink ()
{
  set_name("buttermilk");
  add_name("sourmilk");
  set_pname("buttermilks");
  add_adj(({"cup"}));
  set_short("cup of buttermilk");
  set_pshort("cups of buttermilks");
  set_long("This is a nice cup of buttermilk that is a "+
           "frequent drink of citizens of SaMorgan.\n");
  set_soft_amount(45);
  add_prop(HEAP_I_UNIT_VOLUME, 55);
  add_prop(HEAP_I_UNIT_VALUE, 75);
}
