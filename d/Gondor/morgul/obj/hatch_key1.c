inherit "/std/key";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tunnel/tunnel_door.h"

void create_key()
{
    add_name(HATCH_KEY1);
    set_adj(({"small","brass"}));
    set_long("A small key wrought from brass.\n");
    set_key(HATCH_KEY1);

    add_prop(OBJ_I_WEIGHT,120);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,25);
}
