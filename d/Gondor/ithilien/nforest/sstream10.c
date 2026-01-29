/*
 *	/d/Gondor/ithilien/nforest/sstream10.c
 *
 *	Coded by Olorin, 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *   04-Okt-2008, Eowul:    Added drinking support
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Rabbit = allocate(3 + random(4));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("The land is steep and rocky here, and the stream " +
	"is rushing out of a ravine to the east down the slopes towards the " +
        "Anduin. The vale of that great river opens before you to the west, " +
        "with green fields on both sides along the river. The slopes here " +
        "are covered with glades between groups of oak and cedar trees.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "From here the mountains named Ephel Duath appear as dark grey shadows beyond the green hills to the east. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are many miles away now.\n"));
    add_item(({"forest","wood","woods","herbs","glades"}),BS(
    "Many great oaks and cedars are growing here in groups. Between them, wide glades with bushes, " +
    "deep green grasses and herbs cover the slopes. There are thickets of tamarisk and pungent terebinth. " +
    "Thymes are growing in bushes, or with their woody creeping stems mantling in deep tapestries " +
    "the hidden stones. The scent of mints and parsleys hangs heavily in the air. \n"));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}),BS(
    "Primeroles and anemones are awake in filbert-brakes; asphodel and many lily-flowers are nodding their " +
    "half-opened heads in the grass. \n"));
    add_item(({"stream","pool","water"}),BS(
    "The stream has grown considerably and is rushing out of a ravine to the east down the slopes " +
    "towards the Anduin in the west. \n"));

    add_exit(ITH_DIR + "nforest/sstream9","east",0,4);
    add_exit(ITH_DIR + "nforest/sstream11","west",0,4);

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "thyme",
		     HERB_DIR + "fennel",  HERB_DIR + "tarragon",
		     HERB_DIR + "foxglove", }), 
		  ({ "herbs", "flowers", "thickets", "stones", "woods", 
		     "groves"}), 3);
    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_drink_from( ({ "stream", "pool", }) );

    reset_room();
}

public object
clone_npc(object npc, string file)
{
    if (!objectp(npc))
    {
	npc = ::clone_npc(npc, file);
	npc->set_restrain_path(ITH_DIR + "nforest/");
    }
    return npc;
}

public void
reset_room()
{
    set_searched(- random(2));

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 15.0 + rnd() * 90.0);
}

public void
init()
{
    ::init();

    init_drink();
}