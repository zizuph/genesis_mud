/*
 * /d/Gondor/ithilien/forest/haradbanner.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

public int	npc_check();

public void
create_object()
{
    set_name("banner");
    add_name("_harad_banner_from_camp_");
    add_name("flag");
    set_adj("large");
    add_adj("red");
    set_long("This large red banner has a rising sun embroidered in gold in\n"+
	     "the center. It is the symbol of the Southrons from Harad.\n");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);

    add_prop(OBJ_M_NO_GET, npc_check);
}

public int
npc_check()
{
    return this_player()->query_npc();
}

