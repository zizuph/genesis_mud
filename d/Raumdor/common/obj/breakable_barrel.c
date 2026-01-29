#pragma strict_types
#include "defs.h"
inherit STD_DIR + "breakable_container";

void
create_container()
{
    set_name("barrel");
    add_name("wooden");
    set_short("wooden barrel");
    set_long(
      "It is a well-used barrel made of wooden staves and metal hoops.\n");
    add_item(({"hoops", "metal hoops"}),
      "The hoops look to be made of iron and are dinged up from heavy use.\n");
    add_item(({"staves", "wooden staves"}),
      "The staves are grey and worn with nicked and cracked bevels.\n"); 
    add_prop(CONT_I_MAX_VOLUME, 60000); // 60 L, so it can be lifted
    add_prop(CONT_I_MAX_WEIGHT, 60000); // 60 kg 
    add_prop(CONT_I_VOLUME, 10000); // 10 L
    add_prop(CONT_I_WEIGHT, 10000); // 10 kg
    add_prop(CONT_I_RIGID, 1); 
    add_prop(OBJ_I_VALUE, SILVER_VALUE * 2);
}

void
check_break()
{
    try_break_container(10);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    // We risk breaking when dropped, moved, etc.
    set_alarm(0.0, 0.0, &check_break());
}

void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    // We risk breaking from putting more stuff in
    set_alarm(0.0, 0.0, &check_break());
}
