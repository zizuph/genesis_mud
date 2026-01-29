/*
 * /d/Gondor/ithilien/forest/haradtent2.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

object	*Haradrim = allocate(3);

public void	create_gondor();
public void	reset_room();

public void
create_gondor()
{
    set_short("Inside a Haradrim tent");
    set_long(BSN(
	"This reasonably large tent is devoid of furnishings, except "+
	"for the bedrolls stacked along the canvas walls."));
    add_prop(ROOM_I_INSIDE,1);
    add_item( ({ "walls", "bedroll", "bedrolls" }), BSN(
	"The bedrolls are stacked neatly along the walls."));

    add_cmd_item( ({ "bedroll", "bedrolls" }),
	({ "smell", "sniff", "inhale" }),
	BSN("The bedrolls have a faint aroma of sweat."));

    add_exit(ITH_DIR+"forest/haradcamp2","out",0);
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, (NPC_DIR+"haradrim"), 3.0);
}
