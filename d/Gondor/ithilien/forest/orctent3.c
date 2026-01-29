/*
 * /d/Gondor/ithilien/forest/orctent3.c
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
	"The canvas tent walls bow inwards, and the smell is unpleasant. "+
	"Clothes and bedding are jumbled on the ground."));
    add_item( ({ "rolls", "string", "bedding", "bedrolls" }), BSN(
	"Smelly blankets, loosely rolled and tied with string, are underfoot."));
    add_item( ({ "clothes", "clothing" }), BSN(
	"The clothes are drab and none too clean."));

    add_prop(ROOM_I_INSIDE,1);
    add_exit(ITH_DIR + "forest/orccamp3", "out", 0, 1);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Orc, NPC_DIR + "reuruk", -1.0);
}
