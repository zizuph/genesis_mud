/*
 * /d/Gondor/ithilien/forest/orcpath4.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/ithilien/forest/room_tells";


#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

public int	cross_stream();

public void
create_gondor()
{
    set_short("a foul stream in the Ithilien forest");
    set_long(
	"On the north bank of a foul-reeking stream in the "+
	"forest of Ithilien. Misty vapours rise from the stream, and a "+
	"nasty stench permeates the air. A well-used track leads down "+
	"to the stream to the south. On the far side of the stream, "+
	"the track disappears "+
	"into the forest. A stonelaid road runs east and west "+
	"to the north of here.\n");

    add_item( ({ "stonelaid road", "road" }), 
	"The road looks ancient but well-constructed.\n");
    add_item( ({ "vapour", "vapours", "bank", "stream" }), 
	"The vapours shrouding the stream have a foul smell.\n");
    add_item("track", 
	"Across the stream, the track disappears into the forest.\n");
    add_item( ({ "tree", "trees", "forest" }), 
	"The forest grows thickly on either side of the stream.\n");

    add_cmd_item( ({ "stream", "vapour", "vapours", "stench", "smell" }),
	({ "smell", "sniff", "inhale" }),
	"The vapours reek of death.\n");

    add_exit(ITH_DIR+"forest/orcpath3", "south", cross_stream);
    add_exit(ITH_DIR+"road/er2", "north", 0);

    BEACH;
    add_prop("_water_is_poisoned", 1);

    add_orc_camp_tells();
}

public int
cross_stream()
{
    write("You wade across the foul-reeking Morgulduin.\n");
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
