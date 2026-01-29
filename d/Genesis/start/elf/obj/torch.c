/*
 * A torch
 *
 * Made by Nick
 */

inherit "/std/torch";

#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
public string
special_short()
{
    if (query_time() == query_max_time())
        return "fresh tar-drenched";
    else if (query_time() > 30 && query_lit(0))
        return "slowly burning";
    else if (query_time() > 30)
        return "blackened";
    else if (query_time() && query_lit(0))
        return "smoldering";
    else if (query_time())
        return "charred";
    else
        return "burnt out";
}

void
create_torch()
{
    set_name("torch");
    set_pname("torches");	   /* The plural name. */
    set_adj("small");
    set_short("small torch");
/*    set_short("@@special_short@@ torch"); */
    set_long("It is a knaggy stick of wood, wrapped with tar-drenched " +
        "rags at one end.\n");
    set_strength(2);
    set_time(150);
    set_value(40);

    add_prop(OBJ_I_WEIGHT , 1000);
    add_prop(OBJ_I_VOLUME, 1200);
}

string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
    init_torch_recover(arg);
}
