/**********************************************************************
 * - lwine.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("wine");
    set_adj(({"light", "red"}));
    set_short("goblet of light red wine");
    set_pshort("goblets of light red wine");
    set_long("This goblet is filled with light red wine. It has a "+
      "wonderful dry taste that leaves the taste buds longing for "+
      "more.\n");
    set_soft_amount(155);
    set_alco_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 275);
}
