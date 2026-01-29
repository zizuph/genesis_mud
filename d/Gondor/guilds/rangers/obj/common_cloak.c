/*
 *  RANGERS_OBJ + "common_cloak.c"
 *    Cloak of the Rangers of the North
 *  Original code by Elessar
 *  Modification log:
 *    Alto, February 2002. Modified for ranger recode.
 *    Gwyneth, June 2004. Common cloak for all 3 guild houses.
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <macros.h>
#include <stdproperties.h>

inherit RANGERS_OBJ + "cloak_base.c";

public void
create_robe()
{
    set_name("cloak");
    add_name("_common_cloak_");
    set_adj("grey-green");
    set_short("grey-green cloak");
    set_colour("");
    set_long("This is a hooded cloak made of heavy grey-green cloth. " +
        "To help the wearer to walk unseen in dark forests and " +
        "wilderness, the cloak is grey-green in colour. It is large enough " +
        "to fit over a normal cloak or cape.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}
