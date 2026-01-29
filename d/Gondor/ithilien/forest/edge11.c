/*
 * /d/Gondor/ithilien/forest/edge11.c
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

#include "/sys/ss_types.h"
#include "/d/Gondor/defs.h"

#define TRACK_NEEDED 15

public string	long_func();
public string	exa_bushes();
public string	exa_track();

public void
create_gondor()
{
    set_short("In the forests of Ithilien");
    set_long(long_func);

    add_exit(ITH_DIR+"forest/edge1", "west", 0);
    add_exit(ITH_DIR+"forest/orcpost", "east", 0);
    
    add_item( ({ "thicket", "thickets", "bushes", "bush", "twigs", "twig",
	"broken twig", "broken twigs" }), exa_bushes);
    add_item( ({ "tracks", "trail", "footprints", "ground" }), exa_track);
    add_item( ({ "tree", "trees", "woods", "forest", "forests", 
	"oaks", "oak", "larch", "larches", "larch tree", "larch trees" }),
	"The woods of Ithilien are beautiful.\n");

    add_orc_camp_tells();

}

public string            
exa_bushes()
{
    if ( TP->query_skill(SS_TRACKING) > (TRACK_NEEDED / 2) )
	return 
	    "Green bushes grow thickly beneath the trees.  You notice that "+
	    "some of them have broken twigs forming a trail leading east and "+
	    "west, probably made by someone moving carelessly through "+
	    "the thickets.\n";
    return "Green bushes grow thickly beneath the trees.\n";
}

public string
exa_track()
{
    if ( TP->query_skill(SS_TRACKING) > TRACK_NEEDED )
	return "A track leads east and west through the thickets. "+
    	    "You find some footprints that clearly were made by orcs!\n";
    return "You don't find any tracks here.\n";
}

public string
long_func()
{
    string long;

    long = "The forests of southern Ithilien extend in all directions. " + 
    	   "Oaks with broad green leaves and tall slender larch trees stretch "+
	   "towards the sky, and bushes grow thickly beneath the trees. ";
    if ( TP->query_skill(SS_TRACKING) > TRACK_NEEDED )
	long += "Some sort of trail leads east and west here; footprints "+
		"and a few broken twigs seem to indicate the trail is in use.";

    return long + "\n";
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
