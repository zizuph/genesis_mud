#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/object";

int time;
object pirate;

void create_object()
{
   seteuid(getuid());
   set_name(PIRATE_STANCE_OBJECT);

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);
   add_prop(OBJ_I_VALUE, 0);

   set_no_show();
}

void
stop_stance()
{
    pirate->catch_msg("The intoxicating effect of the booze begins to disappear.\n");
    tell_room(E(pirate), " begins to act a bit less intoxicated.\n", pirate, TO);

    remove_object();
}

void
do_stance()
{
   TP->add_prop(I_AM_IN_PIRATE_STANCE,1);
   set_alarm(1000.0,0.0, &stop_stance());
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        remove_object();
        return;
    }

    if(!living(to))
    {
        remove_object();
        return;
    }

    pirate = to;
    do_stance();
}
