inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>
void
create_object()
{
    set_name("vamp_vsay");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
}

public int
vsay(string str)
{
    return VAMP_ABILITIES->vsay(str, 1);
}

void
init()
{
    ::init();
    add_action(vsay, "'", 2);
}

void
remove_vsay_ob()
{
    remove_object();
}
