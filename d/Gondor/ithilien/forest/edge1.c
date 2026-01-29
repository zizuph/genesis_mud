/*
 * /d/Gondor/ithilien/forest/edge1.c
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
#include "/sys/ss_types.h"

#define TRACKING_NEEDED 40
#define AWARE_NEEDED    30

int		Discovered;

public string	long_func();
public string	exa_bushes();
public string	exa_track();

public void
create_gondor()
{
    set_short("Between forest and river in Ithilien");
    set_long(long_func);
    add_exit(ITH_DIR+"forest/edge2", "north", 0);
    add_exit(ITH_DIR+"forest/edge0", "south", 0);
    add_exit(ITH_DIR+"osgiliath/boatplace", "west", 0);
    add_exit(ITH_DIR+"forest/edge11", "east", 0);
    add_item( ({ "branches", "bushes", "twig", "bush" }), exa_bushes);
    add_item( ({ "tracks", "track" }), exa_track);
    add_item( ({ "trees", "tree", "oak", "oaks", "larch", "larches",
	"woods", "forest" }), 
	BSN("Great oaks and tall larches make up the forest."));
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(HERB_DIR+"garlic");
    set_search_places(({"bushes","forest","herbs"}));

    add_orc_camp_tells();
}

public string
long_func()
{
    int track;
    string longdesc;
    longdesc =
	"Large oak trees make up the forest to the east. Tall "+
	"larches can be seen here and there, and broadleaved bushes "+
	"grow all around. The river Anduin flows past just to the west. ";

    track = TP->query_skill(SS_TRACKING);
    if ( track >= TRACKING_NEEDED )
    {
	Discovered = 1;
    	if ( (track - 10) >= TRACKING_NEEDED )
	    longdesc += "Some half-hidden tracks, obviously made by orcs, "+
	    		"lead into the forest.";
	else
	    longdesc += "Some half-hidden tracks lead into the forest.";
    }
    else if ( TP->query_skill(SS_AWARENESS) >= AWARE_NEEDED )
	longdesc += "Some of the bushes have broken branches.";


    return longdesc + "\n";
}

public string
exa_bushes()
{
    string desc = "The bushes have broad green leaves. ";

    if ( TP->query_skill(SS_AWARENESS) > (AWARE_NEEDED / 2) )
	desc += "Some bushes have broken branches, as if something "+
		"has passed through them. ";
    if ( TP->query_skill(SS_TRACKING) > (TRACKING_NEEDED / 2) ) 
    {
	Discovered = 1;
        desc += "Pushing aside the leaves, you discover tracks on "+
		"the ground beneath them.";
    }
    return desc + "\n";
}

public string
exa_track()
{
    if (!Discovered) return "You don't see any tracks here.\n";
    if ( (TP->query_skill(SS_TRACKING) - 10) >= TRACKING_NEEDED )
	return "The tracks clearly lead east into the forest, and you are "+
	    "absolutely positive that orcs made them.\n";
    return "The tracks lead east into the forest.\n";
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
