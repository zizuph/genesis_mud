/**********************************************************************
 * - mead.c                                                         - *
 * -                                                                - *
 * - Created by Tapakah, 07/2021                                    - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

void
create_drink ()
{
  set_name("mead");
  set_pname("meads");
  set_adj(({"golden"}));
  set_short("tankard of golden mead");
  set_pshort("tankards of golden mead");
  set_long("This tankard is filled with golden sparkling mead. "+
           "The sweet honey and the yeast the mead is made from "+
           "produce a distinct pleasant smell.\n");
  set_soft_amount(105);
  set_alco_amount(30);
  add_prop(HEAP_I_UNIT_VOLUME, 65);
  add_prop(HEAP_I_UNIT_VALUE, 155);
}
