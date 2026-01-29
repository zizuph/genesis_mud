inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#define   I_FOUND_LEFT_HORN    "_i_found_left_horn_ansalon"
#include "/d/Krynn/common/defs.h"

void create_object()
{
    set_name("horn");
    add_name("left horn");
    set_adj("left");
    add_adj("stone");
    set_long("This is a heavy left horn made out of stone, you wonder "+
             "where it comes from...\n");

    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 0);
}

