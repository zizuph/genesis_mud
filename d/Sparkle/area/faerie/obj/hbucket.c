#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/container";

object honey;

void
create_container()
{
    set_name("bucket");
    set_adj("wooden");
    set_short("wooden bucket");
    set_long("This is a round wooden bucket. It is deep and well used. " +
        "The inside is stickly looking, like it is used to store honeycombs.\n");

    add_prop(CONT_I_WEIGHT, 130);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_MAX_VOLUME, 10000);

    add_prop(OBJ_I_VALUE, 200);

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

}

public void
leave_inv(object ob, object from)
{
    ::enter_inv(ob, from);
write (honey_count+ "\n");
}


public int
prevent_enter(object ob)
{
    if (!ob->id("honeycomb"))
    {
        write("You may only honeycombs in " + short() + ".\n");
        return 1;
    }

    return 0;
}
