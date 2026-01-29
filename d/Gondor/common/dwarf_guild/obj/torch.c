/*
 * /d/Gondor/common/dwarf_guild/obj/torch.c
 *
 * Just a generic torch that is sold in the Rockfriend Guild.
 *
 * /Mercade, 11 Februari 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/torch";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("small");

    set_short("small torch");
    set_pshort("small torches");

    set_long("It is a small torch, yet strong enough to shed light in " +
	"darkness.\n");

    set_keep();
    set_strength(1);
    set_time(300);
    set_value(60);

    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_WEIGHT, 1000);
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":" + query_keep_recover() + query_torch_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_torch_recover(arg);
}
