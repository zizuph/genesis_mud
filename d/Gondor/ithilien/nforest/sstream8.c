#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Scout;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("broad ledge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("The land is steep here, and you hear the sounds " +
        "of a stream to the south, rushing through a narrow channel " +
        "and over many terraces. But a steep rock wall blocks your " +
        "view to the south. You can follow the foot of the rock to " +
        "the southwest or southeast. The trees are larger and more " +
        "scattered here than on the slopes further to the east. " +
        "Giant oaks and cedar trees are growing in wide glades. " +
        "The Vale of Anduin opens before you far to the west, with " +
        "its green fields along the great river.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
	BSN("From here the mountains named Ephel Duath appear as " +
        "dark grey shadows beyond the green hills to the east. "+
        "You judge the mountains to be between 5000 to 7000 feet tall, "+
        "and you guess they are several leagues away now.\n"));
    add_item(({"forest","wood","woods","herbs","glades","thickets",
        "thicket"}), BSN("Many great trees are growing here. Giant " +
	"oaks and cedar trees are standing in wide glades. Between " +
	"the trees, bushes and thickets are blocking your path to " +
	"the north. Herbs of many kinds are putting forth their " +
        "flowers and fill the air with their scents."));
    add_item(({"cliff","wall","rock","rock wall"}), BSN(
        "The rock wall rises with a sheer cliff face to the south. " +
        "There is no way to climb it."));
    add_item(({"stream","pool","water"}), BSN(
        "Here and there are little pools in the grass where falling " +
        "streams are halted in cool hollows on their journey down to " +
        "the Anduin. One of the larger streams can be seen beyond " +
        "the thickets to the north."));

    set_up_herbs( ({ HERB_DIR+"caraway", HERB_DIR+"savory", 
                         HERB_DIR+"ginger", HERB_DIR+"garlic",
                         HERB_DIR+"suranie", }),
        ({"herbs","flowers","thickets","glades","woods","ledge"}), 3);

    add_exit(ITH_DIR + "nforest/pool","southwest",0,1);
    add_exit(ITH_DIR + "nforest/sstream7","southeast",0,4);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    Scout = clone_npc(Scout, NPC_DIR + "std_orc");
    Scout->set_aggressive(1);
    Scout->set_restrain_path(ITH_DIR + "nforest/");
    Scout->set_random_move(25 + random(25));
}

public int 
do_climb(string str)
{
    if ( !strlen(str) || ((str != "tree") && (str != "trees") && 
        (str != treetype) && (str != treetype+" tree") && 
        (str != treetype+" trees") && (str != "wall")))
    {
        NFN("Climb what?");
        return 0;
    }
    if (str == "wall")
        NF("You cannot climb the wall. It is much too steep!\n");
    else
        NF("You cannot climb the " + str + ", as even the lowest branches are too high.\n");
    return 0;
}
