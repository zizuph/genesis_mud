/*
 *	/d/Gondor/ithilien/nforest/sstream5.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	1996, Olorin:	Changed inheritance.
 *   04-Okt-2008, Eowul:    Added drinking support 
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Crow;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("A smaller stream rushing down from the north here joins "
      + "the stream you have been following. On the other side of the stream "
      + "the steep bank continues to the west and east. The stream is "
      + "running down the slopes towards the Anduin. The woodlands grow "
      + "thinner here, and the ground becomes stonier. The smell of flowers "
      + "and herbs fills the air.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "The mountains are hidden by the large trees.\n");
    add_item(({"forest","wood","woods","herbs","groves","thickets","thicket",
	"grove"}),BSN("Many great trees are growing here, planted long ago, "
      + "falling into untended age amid a riot of careless descendants. "
      + "There are olive and cedar, cypress and myrtles, and thymes growing "
      + "in bushes, or with their woody creeping stems mantling in deep "
      + "tapestries the hidden stones, and many other herbs of different "
      + "forms and scents."));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}),
	BSN("Primeroles and anemones are awake in filbert-brakes; asphodel "
      + "and many lily-flowers are nodding their half-opened heads in the "
      + "grass."));
    add_item(({"stream","pool","water"}), BSN(
        "Here and there are little pools in the grass where falling streams "
      + "are halted in cool hollows on their journey down to the Anduin. "
      + "The stream that you have been following is joined by a smaller "
      + "stream here and rushes ever downward towards the Anduin."));

    add_exit(ITH_DIR + "nforest/sstream4","southeast",0,4);
    add_exit(ITH_DIR + "nforest/sstream6","southwest",0,4);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_drink_from( ({ "stream", "pool", }) );

    set_up_herbs( ({ HERB_DIR+"attanar", HERB_DIR+"hemlock", HERB_DIR+"oregano",
		     SHIRE_HERB_DIR+"parsley", HERB_DIR+"tarragon", }),
		  ({ "ground","field","flowers","bushes","thickets","forest"}), 3);

    reset_room();
}

public void
reset_room()
{
    set_searched(-2);

    if (objectp(Crow))
	return;

    Crow = clone_npc(Crow, NPC_DIR + "crow");
    Crow->set_restrain_path(ITH_DIR);
    Crow->set_random_move(5);
}

public void
init()
{
    ::init();

    init_drink();
}
