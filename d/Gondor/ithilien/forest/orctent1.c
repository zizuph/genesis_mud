/*
 * /d/Gondor/ithilien/forest/orctent1.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 30-Dec-1997, Gnadnar: vary descriptions
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Orc = allocate(3);

public void
create_gondor()
{
    set_short("inside a small tent");
    set_long(BSN(
	"This tent is small and smelly. The canvas ceiling "+
	"is close overhead, and bedrolls and clothing are underfoot."));
    add_item("belongings", BSN(
	"Bedrolls and clothing are scattered around the tent."));
    add_item( ({ "bedding", "bedrolls" }), BSN(
	"The bedrolls clearly see heavy use and infrequent cleanings."));
    add_item( ({ "clothes", "clothing" }), BSN(
	"The clothing is drab grey and black, occasionally "+
	"marked with an emblem of a red eye."));

    add_prop(ROOM_I_INSIDE,1);
    add_exit(ITH_DIR+"forest/orccamp1", "out", 0, 0);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Orc, NPC_DIR + "reuruk", -1.0);
}
