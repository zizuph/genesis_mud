/*  The cloaks of the rangers of Ithilien */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/obj/ranger_cloak.c";

#include "/d/Gondor/defs.h"

public void
create_cloak()
{
    set_adj(({"dark-green", "green", }));
    set_short("dark-green cloak");
    set_long("This is a hooded cloak made of heavy dark-green cloth. "
	   + "To help the wearer to walk unseen in dark forests and "
	   + "hills, the cloak is dark-green in colour.\n");
}
