/*
   torch.c

   A sample torch
*/
inherit "/std/torch";

#include <stdproperties.h>

create_torch()
{
   set_name("branch");
   set_adj(({"dried", "ancient"}));
    add_name("ancient_branch");
  set_long("It is a small branch, broken from some dried ancient tree.\n");
    add_prop(OBJ_I_LIGHT,0);
}

