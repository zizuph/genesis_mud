inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#define   I_FOUND_FINGER    "_i_found_finger_ansalon"
#include "/d/Krynn/common/defs.h"

void create_object()
{
    set_name("finger");
    set_adj("marble");
    set_long("This is a heavy finger made out of marble, you wonder "+
             "where it comes from...\n");

    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 0);
}

