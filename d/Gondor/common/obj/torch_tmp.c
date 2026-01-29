/*
 * /d/Gondor/common/obj/torch_tmp.c
 *
 * This torch will destruct once it is burned out.
 */
inherit "/d/Gondor/common/obj/torch";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_torch()
{
  ::create_torch();
}

/*
 * Function name: burned_out
 * Description:	  If this function is called the torch has burned out.
 */
void
burned_out()
{
    object ob = environment();

    set_alarm(10.0, 0.0, remove_object);

    ::burned_out();

    if ((!ob->query_prop(ROOM_I_IS)) && (!living(ob)) &&
        (objectp(environment(ob))))
    {
        ob = environment(ob);
        if (ob->query_prop(ROOM_I_IS))
            tell_room(ob, "The " + short() + " in the " +
              environment(this_object())->short() + " goes out.\n");
    }
}
