inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Krynn/common/defs.h"

void create_container()
{
    set_name("corpse");
    set_short("corpse of a tiny brown-haired male kender");
    set_long("This is the dead body of a tiny brown-haired "+
             "kender.\n");

    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, 1);

}

