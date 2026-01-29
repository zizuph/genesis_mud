/**********************************************************************
 * - dale.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("ale");
    set_adj(({"dark"}));
    set_short("cup of dark ale");
    set_pshort("cups of dark ale");
    set_long("This cup is brimming to the top with dark ale and "+
      "there is a nice frothy head on top that makes it even better "+
      "to drink.\n");
    set_soft_amount(155);
    set_alco_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 100);
    add_prop(HEAP_I_UNIT_VALUE, 175);
}
