/* This is the object that blocks the exit for the enemy of a knight */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

inherit "/std/object";

static object block_obj;

public void
create_object()
{
    set_name("blblblbl");
    add_name("knight_block_control_object");
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    seteuid(getuid(TO));
}

public void
init()
{
    add_action("do_check","",1);
    ::init();
}

static int
do_check(string str)
{
    if (!block_obj || !block_obj->attack_and_environment_check())
      set_alarm(1.0,0.0,"remove_object");
    return 0;
}

public void
set_block_object(object what)
{
    block_obj = what;
}
