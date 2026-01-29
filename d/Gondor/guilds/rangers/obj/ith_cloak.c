/*
 *  RANGERS_OBJ + "green_cloak.c"
 *    Cloak of the Rangers of the North
 *  Original code by Elessar
 *  Modification log:
 *    Alto, February 2002. Modified for ranger recode.
 *
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
    add_name("_RoI_cloak_");
    set_adj(({"dark-green", "green", "spotted" }));
    set_short("dark-green spotted cloak");
    set_colour("green");
    set_long("This is a hooded cloak made of heavy dark-green cloth. "
      + "To help the wearer to walk unseen through glades and "
      + "forests, the cloak is spotted in various hues of brown and "
      + "green. It is large enough to fit over a normal cloak or cape.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}
