#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
inherit "/std/object";

#pragma strict_types;

void
create_object()
{
   set_name(({"ship","boat","vessel"}));
   set_short("solid oak boat");
   set_long("It's a solid oak boat. Small however, only " +
      "enough room for one person it seems. "+
      "The sails are gently flapping "+
      "in the wind. \n");
   add_item("ketting", "The ketting is of solid iron. The ketting "+
      "is full of sheep hair. \n");
   add_item("hair", "The sheep hair is very soiled. \n");
   add_prop(OBJ_I_WEIGHT,300000);
}

