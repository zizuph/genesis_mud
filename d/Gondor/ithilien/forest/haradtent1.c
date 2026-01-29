/*
 * /d/Gondor/ithilien/forest/haradtent1.c
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

public void
create_gondor()
{
    set_short("Inside a Haradrim tent");
    set_long(BSN(
	"The canvas roof of this tent is close overhead. "+
	"A few bedrolls lie underfoot, and smelly clothing, bright "+
	"in colour and decoration, is scattered about."));
    add_prop(ROOM_I_INSIDE,1);
    add_item( ({ "bedroll", "bedrolls" }), BSN(
	"The bedrolls clearly see a lot of hard use.  They're dirty, "+
	"and they smell bad."));
    add_item("clothing", BSN(
	"The clothing is coloured brightly in red and yellow, "+
	"and sometimes even in gold."));

    add_cmd_item( ({ "bedroll", "bedrolls", "clothing", "clothes" }),
	({ "smell", "sniff", "inhale" }),
	BSN("The bedrolls and the clothing both have the ripe "+
	    "aroma of sweaty, unwashed bodies."));

    add_exit(ITH_DIR+"forest/haradcamp1","out",0);
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, (NPC_DIR+"haradrim"), 3.0);
}
