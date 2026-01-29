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
    add_name("chick");
    add_name("stuffed");
    set_adj("soft");
    set_adj("plush");
    add_adj("yellow");
    set_short("soft easter chick");
    set_long("This is a soft easter chick. It is small and yellow colored. It has small wings and small button eyes. The chick looks cute and snuggleable.\n");
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 120);
}


int
do_snuggle(string str)
{
    if((str == "chick"))
    {
        write("You snuggle the " + query_short() + " tightly.\n");
        say(QCTNAME(TP)+ " snuggles " + HIS_HER(TP) + " " + 
            query_short() + " tightly.\n");
        return 1;
    }
    else
    {
        notify_fail("Snuggle what, the chick?\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action("do_snuggle", "snuggle");
}
