/*
   torch.c

   A sample torch
*/
inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("skull"); set_pname("skull");
    set_short("skull"); set_pshort("skulls");
    set_adj("elven");
    set_long("It looks to be an elven skull.\n");
}

