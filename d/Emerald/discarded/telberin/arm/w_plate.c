inherit "/std/armour";

#include "default.h"
#include <wa_types.h>
#include <stdproperties.h>

string
create_armour()
{
        set_name("platemail");
        set_short("white platemail");
        set_long("Elegant carvings decorate this platemail, whose white " +
                 "colour stems from the magics wrought by the elven smiths " +
                 "on it's manufacture.\n");
        set_adj("white");

        set_ac(40);
        add_prop(OBJ_I_VALUE, 755);
        add_prop(OBJ_I_WEIGHT, 5000);
        add_prop(OBJ_I_VOLUME, 4320);
        set_at(A_TORSO);
}
