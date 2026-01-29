/**********************************************************************
 * - dale.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>

inherit "/std/drink";

public void
create_drink()
{
    set_name("ale");
    set_adj(({"dark"}));
    set_short("goblet of dark ale");
    set_pshort("goblets of dark ale");
    set_long("This goblet is filled with dark ale. It has a "+
             "strong malt taste that leaves the taste buds longing for "+
             "more.\n");
    set_soft_amount(155);
    set_alco_amount(65);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 300);
}
