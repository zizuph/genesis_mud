/**********************************************************************
 * - smilk.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("milk");
    add_adj(({"cup", "strawberry"}));
    set_short("cup of strawberry milk");
    set_pshort("cups of strawberry milk");
    set_long("This is a favorite SaMorgan drink especially among children. "+
      "It consists of a mixture of crushed ripened strawberries mixed "+
      "with fresh milk to make a nice cup of fresh strawberry milk.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 55);
    add_prop(HEAP_I_UNIT_VALUE, 75);
 }
 