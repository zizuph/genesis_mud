/*
 *  RANGERS_OBJ + "grey_cloak.c"
 *    Cloak of the Rangers of the North
 *  Original code by Elessar
 *  Modification log:
 *    Alto, February 2002. Modified for ranger recode.
 *    Gorboth, Nov. 2014. Changed inheritance to increase functionality.
 *
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <macros.h>
#include <stdproperties.h>

inherit (RANGERS_OBJ + "conceal_cloak_base1");

public void
create_robe()
{
    set_name("cloak");
    add_name("_RoN_cloak_");
    set_adj(({"dark-grey", "grey", }));
    set_short("dark-grey cloak");
    set_colour("grey");
    set_long("This is a hooded cloak made of heavy dark-grey cloth. " +
        "The cloak is well designed for protection against wind and " +
        "rain. The subtle colouration of its fabric suggests it would " +
        "be helpful for going about unnoticed by casual observers. " +
        "It is large enough to fit over a normal cloak or cape.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}
