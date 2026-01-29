/*
 *  RANGERS_OBJ + "brown_cloak.c"
 *    Cloak of the Ranger Apprentices
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
    add_name("_Rapp_cloak_");
    set_adj(({"dark-brown", "brown", }));
    set_short("dark-brown cloak");
    set_colour("brown");
    set_long("This is a hooded cloak made of heavy dark-brown cloth. "
        + "To help the wearer to keep warm in the wilderness, the cloak "
        + "is made of thick cloth, though it is quite nice and soft. "
        + "It is large enough to fit over a normal cloak or cape.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}
