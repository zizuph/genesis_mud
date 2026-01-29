inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("horn");
   set_adj("minotaur");
   add_adj("elaborately-carved");
   add_adj("carved");
   set_short("elaborately carved minotaur horn");
   set_long("The horn of a minotaur, elaborately carved with tribal markings. " +
        "You imagine this would be worth a bit of gold!\n");
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VALUE, 600);
}