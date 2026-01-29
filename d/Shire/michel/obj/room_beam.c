inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"


create_object()
{
     set_name("beam");
    add_name("_shire_room_beam_");
     add_adj(({"wooden","splintery"}));
    set_short("wooden beam propping the ceiling");
    set_long("This is a splintery "+short()+".\n");

     add_prop(OBJ_I_WEIGHT, 1500);
     add_prop(OBJ_I_VOLUME, 2500);
     add_prop(OBJ_I_VALUE, 15);

}
