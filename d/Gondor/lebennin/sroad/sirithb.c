/*
 * /d/Gondor/lebennin/sroad/sirithb.c
 *
 * Revision History:
 *    5/15/98 - Added path toward quest item by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"


public void	create_gondor();


/* 
 * Function name:    create_gondor
 * Description:      create a spot along a road
 */
void
create_gondor()
{
    set_short("On a bridge");
    set_long(BSN("An old stone bridge crosses the river Sirith here. "+
        "The road runs northeast to southwest, connecting Pelargir to "+
        "Linhir upon Gilrain and Dol Amroth."));


    add_exit(PELAR_DIR + "streets/s_gate_out", "northeast", 0, 2);
    add_exit(LEB_DIR + "sroad/sr1", "southwest", 0, 2);
    add_exit("path1", "south", 0, 0, 1);
    add_item( ({ "bridge", "stone bridge", "old bridge", "old stone bridge",
        "here" }), BSN("Just outside the city walls, the road crosses "+
        "the Sirith on an old stone bridge wide enough for ox carts. "+
        "It spans the river in three arches that rest on the opposite "+
        "riverbanks, and on two mighty stone pillars built into the "+
        "riverbed. A small path leaves the main road and descends into "+
        "the brush beside the river."));

    add_item( ({ "path", "small path" }), BSN("It appears that someone "+
        "has made a habit of leaving the main road here toward the "+
        "south and beaten a path along the river's edge."));

    add_item( ({ "sirith", "river", "river sirith", "branch",
	"southern branch" }),
        BSN("The southern branch of the Sirith River flows serenely "+
        "under the bridge as it makes its way to join with the mighty "+
        "Anduin."));

    add_item( ({ "road", "pathway", "main road" }), BSN("Northeast toward "+
        "the city, the road is paved with cobblestones, but toward the "+
        "southwest it continues as a hardpan pathway."));

    add_item("northeast", BSN("The road toward the northeast leads to "+
        "the southern entrance of the port city of Pelargir."));

    add_item("southwest", BSN("To the southwest, the road vanishes "+
        "into the Gondor countryside."));

    add_item( ({ "city", "pelargir", "city of pelargir", "port city" }),
        BSN("Pelargir upon Anduin is the second largest city of "+
        "Gondor, and the largest harbour of the realm. The city gates "+
        "are to the northeast on the northern bank of the Sirith."));

    add_item( ({ "linhir upon gilrain", "linhir", "gilrain" }),
	BSN("Linhir and the River Gilrain are far too distant to be " +
	"visible from here."));

    add_item( ({ "dol amroth", "dol", "amroth", "citadel",
	"coastal citadel" }),
        BSN("The coastal citadel of Dol Amroth lies much too far to the "+
        "west to be visible from here."));

    add_item( ({ "wall", "walls", "city walls" }), BSN("The city walls of "+
        "Pelargir rise high above the river Sirith. There are "+
        "battlements atop the walls, and on either side of the city "+
        "gates sits a mighty tower."));

    add_item( ({ "ox carts", "carts", "traffic", "someone", "stonemasons" }),
        BSN("There is no other noticeable traffic on the road right "+
        "now."));

    add_item( ({ "arch", "arches", "three arches", "curves", "spans",
        "stone spans" }), BSN("The graceful curves of the stonework "+
        "spans which support this bridge across the Sirith attest to "+
        "the skill of the stonemasons in this area."));

    add_item( ({ "riverbank", "riverbanks", "opposite riverbanks",
        "ground", "edge", "river's edge", "rivers edge", "water's edge",
        "waters edge", "northern bank", "bank", "side" }), BSN("The ground "+
        "on each side of the river gently slope down to the water's "+
        "edge."));

    add_item( ({ "pillar", "pillars", "stone pillar", "stone pillars",
        "mighty stone pillar", "mighty stone pillars", "columns",
        "stone columns", "great stone columns" }), BSN("Two great "+
        "stone columns rise out of the river to support the "+
        "arches of the bridge."));

    add_item( ({ "riverbed", "bottom" }), BSN("With the river at this "+
        "height, it is quite impossible to see to the bottom."));

    add_item( ({ "brush", "trees", "small trees", "bushes" }), BSN("Small "+
        "trees and bushes native to Gondor line the banks of the "+
        "river."));

    add_item( ({ "mighty anduin", "anduin", "confluence", "rivers" }), 
        BSN("The confluence of the two great rivers cannot be seen "+
        "from here."));

    add_item( ({ "cobblestones", "stones" }), BSN("Smooth round stones "+
        "have been carefully placed to pave the road going "+
        "northeast."));

    add_item( ({ "hardpan", "hardpan pathway", "layer", "hard layer",
        "ground", "solid ground" }), BSN("As it heads southwest, "+
        "the road turns to a hard layer of solid ground."));

    add_item( ({ "gate", "city gate", "gates", "city gates", "entrance",
        "southern entrance", "opening" }), BSN("The opening in the "+
        "city wall is secured by a massive gate that is kept closed "+
        "and locked overnight."));

    add_item( ({ "countryside", "gondor countryside", "fields", "gondor",
        "forests", "realm", "area" }), BSN("The fields and forests of "+
        "Gondor stretch to the southwest."));

    add_item("harbour", BSN("The great harbour of Pelargir is not "+
        "visible from here."));

    add_item( ({ "battlements", "openings" }), BSN("The top of the "+
        "city wall has a series of openings through which the "+
        "guards maintain constant vigil."));

    add_item( ({ "guards", "sentinels" }), BSN("The top of the city "+
        "wall is constantly patrolled by the city's sentinels."));

    add_item( ({ "tower", "towers", "barracks" }), BSN("Towers have "+
        "been erected on each side of the city gates to serve as "+
        "barracks for the city's guards."));

} /* end create_gondor */

