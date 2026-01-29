/*
 * /d/Gondor/mordor/obj/torch.c
 *
 * A torch that is used in Cirith Ungol
 *
 * /Mercade 27 july 1993
 *
 * Revision history:
 */

inherit "/std/torch";

#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

/*
 * The standard create routine.
 */
void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("wooden");
    set_adj("large");
    set_long(BSN("A large wooden torch, used to shed light in surrounding " +
        "darkness."));
    set_strength(2);
    set_short("large wooden torch");
    set_pshort("large wooden torches");

    set_time(1000);
    set_value(100);
}

/*
 * Used to make a (partially burned out) torch recoverable.
 */
string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

/*
 * And used to get the torch back as it was before the recover.
 */
void
init_recover(string arg)
{
    init_torch_recover(arg);
}
