/*
 * /d/Gondor/ithilien/forest/edge2.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

public void
create_gondor()
{
    set_short("The edge of the Ithilien forest");
    set_long("The tall green trees of the Ithilien forest extend east, and the "+
	"river Anduin is to the west. "+
	"Ruins are just visible near the river to the north.\n");
    add_item( ({ "trees", "tree", "oaks", "oak", "larch", "larches", "woods",
	"forest" }),
	"The great oaks and tall larches appear ancient. They probably have "+
	"been growing here for hundreds of years.\n");
    add_item( ({ "river", "anduin", "river anduin" }), 
	"The river Anduin runs past to the west. It looks too wide "+
    	"and its currents too swift to cross.\n");
    add_item( ({ "ruins", "ruin", "city", "osgiliath" }),
	"The ruins are those of Osgiliath, a city long deserted.\n");
    add_item( "ground", "Bushes grow thickly beneath the trees.\n");
    add_item( ({ "flower", "flowers" }), 
	"The flowers have an unusual sweet fragrance.\n");
    add_item( ({ "herbs", "herb" }),
	"The herbs are almost hidden by the other bushes and flowers.\n");
    add_item( ({ "bush", "bushes" }),
	"Flowers and herbs are scattered among the green, "+
	"broad-leaved bushes.\n");

    add_cmd_item( ({ "air", "flowers", "herbs" }),
	    ({ "smell", "sniff", "inhale" }),
	    "The air is sweet with the fragrance of the flowers and herbs.\n");

    set_search_places(({"bushes","flowers","herbs"}));
    add_herb_file(HERB_DIR+"attanar");
    add_herb_file(HERB_DIR+"lothore");
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");

    add_exit(ITH_DIR+"forest/edge1","south",0);
    add_exit(ITH_DIR+"osgiliath/bank2","west",0);

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
