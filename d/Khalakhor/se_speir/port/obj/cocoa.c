/**********************************************************************
 * - scocoa.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("cocoa");
    set_pname("cocoas");
    add_name(({"cup"}));
    set_adj(({"hot", "spiced", "cup"}));
    set_short("cup of hot spiced cocoa");
    set_pshort("cups of hot spiced cocoa");
    set_long("This cocoa is piping hot and made with sweet spices of "+
      "nutmeg and cinnamon to enhance the cocoa flavor.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 70);
 }
 