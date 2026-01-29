/**********************************************************************
 * - ale.c                                                          - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("ale");
    set_adj(({"light"}));
    set_short("goblet of light ale");
    set_pshort("goblets of light ale");
    set_long("This goblet is filled with light ale. It has a "+
      "smooth malt taste that leaves the taste buds longing for "+
      "more.\n");
    set_soft_amount(155);
    set_alco_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 275);
}