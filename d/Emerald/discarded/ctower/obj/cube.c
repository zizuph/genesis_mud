inherit "/std/object";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";

#include <stdproperties.h>

void
reset_object()
{
    reset_ctower_object();
}

void
create_object()
{
    set_name("cube");
    add_name("ctower_cube");
    set_long("A clear, crystal cube.  Each side looks to be " +
        "about 6 cm long.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 108);

    create_ctower_object();
}
