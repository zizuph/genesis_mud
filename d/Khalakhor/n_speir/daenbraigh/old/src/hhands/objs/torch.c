/*
 * HH torch
 * TAPAKAH, 10/2005
 */

#include <macros.h>

#include "../../hhands/hhands.h"

inherit "/std/torch";

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_torch()
{
    set_name("torch");
    add_name(({"torch",HH_OBJID+"torch"}));
    set_pname("torches");          /* The plural name. */
    set_adj("large");
    set_long("A large torch that looks like a good source of light."+
	     "An emblem of crossed clubs appears on the handle.\n");
    set_strength(3);
    set_short("large torch");
    set_pshort("large torches");
    set_time(1800);
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
