/* Locket by Gwyneth, August 1999 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define WHOLE_LOCKET "/d/Ansalon/private/entrance/obj/locket_whole"

void
create_object()
{
    set_name(({ "locket", "_locket_left_" }));
    set_adj("tarnished");
    add_adj("broken");
    add_adj("silver");
    set_short("tarnished broken silver locket");
    set_long("This tarnished silver locket is only a piece of the whole. " + 
        "The other half with the chain is missing.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 30);
}

void
enter_env(object from, object to)
{
    object right_locket;
    if (right_locket = present("_locket_right_", E(TO)))
    {
        setuid();
        seteuid(getuid());
        right_locket->remove_object();
        clone_object(WHOLE_LOCKET)->move(E(TO));
        write("The two halves of the locket merge together.\n");
        set_alarm(0.1,0.0,"merge_lockets");
    }
    ::enter_env(from, to);
}

void
merge_lockets()
{
    remove_object();
}
