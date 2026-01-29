/*
 * /d/Gondor/ithilien/forest/ncamp2.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"

#define CLAIMING_HARAD_BANNER  "_ranger_i_claiming_harad_banner"
#define DID_VISIT_HARADCAMP  "_ranger_i_did_visit_haradcamp"

static object  Haradrim, Flag;

public void
create_gondor()
{
    set_short("the northern edge of a camp in Ithilien");
    set_long(
	"Damaged trees lean at crazy angles along this edge "+
	"of the clearing. "+
	"Tents and campfires are visible to the south and "+
	"west, and the clearing continues west.\n"); 

    add_item( ({ "camp", "tent", "tents", "clearing" }), 
	"The clearing stretches out south and west. A great number "+
	"of tents have been raised there.\n");
    add_item( ({ "trees", "tree", "forest" }), 
	"Forest extends to the north and east around this clearing. "+
	"Along the edge of the clearing, carelessly hacked trees "+
	"lean at possibly dangerous angles.\n");

    add_exit(ITH_DIR + "forest/haradcamp5n","north",  0);
    add_exit(ITH_DIR + "forest/haradcamp1", "south", 0);
    add_exit(ITH_DIR + "forest/haradcamp2n","east",  0);
    add_exit(ITH_DIR + "forest/ncamp",      "west",  0);

    reset_room();
}

public void
reset_room()
{
    if ( !objectp(Flag) || environment(Flag) != TO)
	(Flag = clone_here(ITH_DIR+"forest/haradbanner"))->move(TO);

    Haradrim = clone_npc(Haradrim, NPC_DIR+"haradrim");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if ( interactive(ob) ) 
    {
	if ( ob->query_prop(CLAIMING_HARAD_BANNER) ) 
	{
	    ob->add_prop(DID_VISIT_HARADCAMP, 2);
	    if ( !objectp(Flag) || environment(Flag) != TO )
		(Flag = clone_here(ITH_DIR+"forest/haradbanner"))->move(TO);
	}
	else 
	    ob->add_prop(DID_VISIT_HARADCAMP, 1);
    }
}
