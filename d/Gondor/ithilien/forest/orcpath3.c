/*
 * /d/Gondor/ithilien/forest/orcpath3.c
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
#include <stdproperties.h>

public int	cross_stream();

public void
create_gondor()
{
    set_short("a foul stream in the Ithilien forest");
    set_long("On the south bank of a foul-reeking stream in the forest of "+
	"Ithilien. Misty vapours rise from the stream, and a nasty stench "+
	"permeates the air. A well-used track leads into the forest to "+
	"the southwest. Across the stream, the track "+
	"continues north into the trees.\n");
    add_item( ({ "vapour", "vapours", "bank", "stream" }), 
	"The foul stream reeks of death.\n");
    add_item( ({ "oak", "oaks", "larch", "larches", "tree", "trees",
	"forest" }), 
	"The forest is composed mainly of oaks and larches.\n");
    add_item("track", 
	"The track leads southwest into the forest.\n");

    add_cmd_item( ({ "stream", "vapour", "vapours", "stench", "smell" }),
	({ "smell", "sniff", "inhale" }),
	"The vapours reek of death.\n");

    add_exit(ITH_DIR+"forest/orcpath2", "southwest", 0);
    add_exit(ITH_DIR+"forest/orcpath4", "north", cross_stream);

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
