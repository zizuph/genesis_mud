#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/food";


void
create_food()
{
    set_name("lemon");
    set_adj("large");
    add_adj("yellow");
    set_long("This is a large yellow melon. The juice from this "
      + "fruit is very sour, and is known to be used in many "
      + "different recipes.\n");
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 200);
}


void
init()
{
    ::init();
    add_action("squeeze_lemon", "squeeze");
}


int
squeeze_lemon(string str)
{
    if (str != "lemon" && str != "large lemon")
    {
        return 0;
    }

    TP->catch_msg("You squeeze the large lemon. The juice pours onto the "
      + "ground and is lost.\n");
    tell_room(E(TP), QCTNAME(TP) + " squeezes a large lemon. The juice "
      + "pours onto the ground and is lost.\n", TP);

    return 1;
}
