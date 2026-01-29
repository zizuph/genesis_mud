/**********************************************************************
 * - stea.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("tea");
    set_pname("teas");
    add_name(({"cup"}));
    set_adj(({"hot", "spiced", "cup"}));
    set_short("cup of hot spiced tea");
    set_pshort("cups of hot spiced tea");
    set_long("This tea is piping hot and made with sweet spices to "+
      "enhance the tea flavor.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 60);
    add_prop(HEAP_I_UNIT_VALUE, 70);
 }
 