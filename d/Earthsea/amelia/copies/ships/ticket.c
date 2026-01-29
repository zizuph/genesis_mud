#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("GontSparkle");
    add_adj("green");
    set_long("This ticket is for the Gont-Sparkle ship.\n");
    add_prop(OBJ_I_VALUE, 24);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP,"@@flerp");
}

flerp()
{
  this_player()->catch_msg("Oh no! The ticket got all dirty! Now surely\n"+
			   "noone would buy it.\n");
  remove_prop(OBJ_I_VALUE);
  return 0;
}