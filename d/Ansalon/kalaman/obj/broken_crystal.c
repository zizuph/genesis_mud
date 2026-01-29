inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
    set_name("crystal");
    add_name("_broken_crystal");
    set_adj("broken");
    add_adj("blue-tinged");
    set_short("broken blue-tinged crystal");
    set_long("This is a long blue-tinged crystal that has been broken in half. "+
      "It looks rather dull and uninteresting.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 100);

}

