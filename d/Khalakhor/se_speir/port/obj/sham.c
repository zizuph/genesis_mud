/**********************************************************************
 * - sham.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("ham");
    set_pname("hams");
    set_adj(({"slice", "cured", "honey"}));
    set_short("slice of honey cured ham");
    set_pshort("slices of honey cured ham");
    set_long("This slice of ham has been cured with honey which "+
      "gives it a sweet honey flavor that simply melts in the "+
      "mouth with goodness.\n");
    set_amount(100);
    add_prop(HEAP_I_UNIT_VOLUME, 80);
    add_prop(HEAP_I_UNIT_VALUE, 50);
}
