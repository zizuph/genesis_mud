/**********************************************************************
 * - milk.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("milk");
    set_adj(({"milks", "white", "fresh"}));
    add_name(({"cup", "white"}));
    set_short("cup of fresh milk");
    set_pshort("cups of fresh milk");
    set_long("This is a nice cup of fresh milk.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 55);
    add_prop(HEAP_I_UNIT_VALUE, 45);
 }
 