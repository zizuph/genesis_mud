inherit "/std/key";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";

#include <stdproperties.h>

void
reset_key()
{
    reset_ctower_object();
}

void
create_key()
{
    set_long("A small, clear, crystal key.\n");
    set_name("key");
    set_adj("crystal");
    set_key("ctower_quest_key");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 72);

    create_ctower_object();
}
