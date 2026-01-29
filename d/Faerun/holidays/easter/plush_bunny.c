inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

string
query_auto_load()
{
    return MASTER;
}

void
create_object()
{
    add_name("bunny");
    add_name("stuffed");
    set_adj("soft");
    set_adj("plush");
    add_adj("white");
    set_short("soft easter bunny");
    set_long("This is a soft easter bunny. It is plush and silky looking " +
        "with long ears and button eyes. The easter bunny is white and " +
        "looks squeezable.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 120);
}


int
do_squeeze(string str)
{
    if((str == "bunny"))
    {
        write("You squeeze the " + query_short() + " tightly.\n");
        say(QCTNAME(TP)+ " squeezes " + HIS_HER(TP) + " " + 
            query_short() + " tightly.\n");
        return 1;
    }
    else
    {
        notify_fail("Squeeze what, the bunny?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action("do_squeeze", "squeeze");
}
