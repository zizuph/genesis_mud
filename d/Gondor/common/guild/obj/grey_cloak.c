/*  The cloaks of the rangers of Ithilien */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/obj/ranger_cloak.c";

#include "/d/Gondor/defs.h"

public void
create_cloak()
{
    set_adj(({"dark-grey", "grey", }));
    set_short("dark-grey cloak");
    set_long(BSN("This is a hooded cloak made of heavy dark-grey cloth. "
      +	"To help the wearer to walk unseen in the darkness of night, the "
      + "cloak is dark-grey in colour."));

    set_hood_adjs( ({ "grey-cloaked", "hooded" }) );
}
