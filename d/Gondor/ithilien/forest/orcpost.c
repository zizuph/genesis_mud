/*
 * /d/Gondor/ithilien/forest/orcpost.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 30-Dec-1997, Gnadnar:	inherit camp.c
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#define DID_VISIT_ORCCAMP "_ranger_visited_orccamp"

static object *Orc = allocate(2),
               Flag;

public void
create_camp()
{
    set_short("an orcish guardpost in Ithilien");
    set_long("The forest thins to the east, opening into a large clearing. "+
	"A few logs have been placed between two piles of rocks to "+
	"form a primitive "+
	"barricade, and a tattered black and red banner hangs from a pole, "+
	"suggesting that this is a guardpost of a troop of Red Eye Orcs. "+
	"Woods continue to the north, west and south.\n");
    add_item( ({ "wall", "palisade", "barricade" }), 
	"The barricade is primitive, but will probably " +
        "help the defenders avoid most of the less random arrows. It stands " +
        "about three feet tall.\n");
    add_item("logs", 
	"A few logs have been placed between piles of rocks to form "+
	"a primitive palisade.\n");
    add_item("banner", 
	"The banner is red, with a circular black field in the center. "+
	"Upon the black field is embroidered the image "+
	"of a red, lidless eye.\n");
    add_item( ({ "pole", }),  
        "The flag pole is made from a thin tree trunk. "+
	"It looks rather crooked and lop-sided.\n");
    add_item("clearing", 
	"The clearing stretches out east behind the palisade.\n");
    add_item( ({ "piles", "piles of rocks", "rocks" }), 
	"The rocks have been piled up to support the logs of the palisade.\n");
    add_item( ({ "woods", "forest", "tree", "trees" }), 
	"The forest extends to the north, west and south.\n");

    set_move_msg("climb over the palisades");

    add_exit(ITH_DIR + "forest/orcpost2", "east", check_allow, 1);
    add_exit(ITH_DIR + "forest/edge11",   "west", 0, 1);

    reset_room();

    add_orc_camp_tells();
}

public void
reset_room()
{
    ::reset_room();
    if (!objectp(Flag))
    {
	Flag = clone_object(ITH_DIR + "forest/redeyebanner");
	Flag->move(TO);
    }
    clone_npcs(Orc, NPC_DIR + "reorc", -1.0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_ORCCAMP, 1);

    if(interactive(ob))
    {
        start_room_tells();
    }

}
