/*
 * /d/Gondor/ithilien/forest/orcpath2.c
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

public void
create_gondor()
{
    set_short("A well-used track in the Ithilien forest");
    set_long("A dirty track runs from the northeast to the south. The " +
        "forest seems to grow thinner to the north, but looks still quite " +
        "dense in the other directions. Broken branches are hanging " +
        "from the trees along the path, and some of the ancient trees " +
        "have crude carvings in the trunks. The forest is oddly silent, " +
        "lacking the usual sounds of birds and small wildlife.\n");
    add_item("trees", 
	"Several of the trees along the track have been broken down. "+
    	"Others still standing have crude carvings in the bark.\n");
    add_item("carvings", 
	"The carvings mostly depict a lidless eye and other foul images.\n");
    add_item("track", 
	"The track seems to get a lot of use.\n");

    add_exit(ITH_DIR+"forest/orcpath1","south",0);
    add_exit(ITH_DIR+"forest/orcpath3","northeast",0);

    add_orc_camp_tells();
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
