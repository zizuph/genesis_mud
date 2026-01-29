#pragma save_binary

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/hobbit/hobbitdefs.h"
#include "/d/Shire/common/defs.h"

create_object()
{
   set_name("driftwood");
   add_adj("wet");
   set_long("It appears to be some sort of wood. It looks wet, you guess "+
            "it has been in the water for quite a while now.\n");
   add_prop(OBJ_I_WEIGHT, 4);
    add_prop(OBJ_I_VOLUME, 6);
   add_prop(OBJ_I_VALUE, 0);
}