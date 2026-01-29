/**********************************************************************
 * - cmilk.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
    set_name("chocolate");
    add_name(({"cup", "milk"}));
    set_short("cup of chocolate milk");
    set_pshort("cups of chocolate milk");
    set_long("This is a nice cup of fresh milk that has had finely "+
      "powdered chocolate added to it to make a nice cup of chocolate "+
      "milk.\n");
    set_soft_amount(45);
    add_prop(HEAP_I_UNIT_VOLUME, 55);
    add_prop(HEAP_I_UNIT_VALUE, 75);
 }