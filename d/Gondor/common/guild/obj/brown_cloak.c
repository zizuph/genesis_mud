/*  The cloaks of the rangers of Gondor */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/obj/ranger_cloak.c";

#include "/d/Gondor/defs.h"

public void
create_cloak()
{
    set_adj(({"dark-brown", "brown", }));
    set_short("heavy dark-brown cloak");
    set_long(BSN("This is a hooded cloak made of heavy dark-brown cloth. "
      + "To help the wearer to keep warm in the wilderness, the cloak "
      + "is made of thick cloth, though it is quite nice and soft."));
    set_hood_adjs( ({ "brown-cloaked", "hooded" }) );
}
