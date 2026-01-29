/**********************************************************************
 * - rwine.c                                                        - *
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
    set_adj(({"dark", "red"}));
    set_short("goblet of dark red wine");
    set_pshort("goblets of dark red wine");
    set_long("This goblet is filled with dark red wine. It has a "+
      "surprisingly sweet taste considering most wines in this area "+
      "is dry.\n");
    set_soft_amount(155);
    set_alco_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 275);
}
