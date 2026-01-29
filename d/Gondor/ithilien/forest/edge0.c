/*
 * /d/Gondor/ithilien/forest/edge0.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Gondor/ithilien/forest/room_tells";


#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("the western edge of the Ithilien forest");
    set_long("The great river Anduin runs just beyond this western edge of "+
	"the Ithilien forest. The forest consists of tall oaks and larches; "+
	"broad-leaved bushes and shrubberies grow alongside the river.\n");
    add_item(({"river", "anduin", "river anduin", }), 
        "The great river Anduin flows just west of the forest edge, on its "+
	"way south towards the Sea. The river is wide and strong.\n");
    add_item("forest",
	"The green forests of Ithilien might very well resemble "+
    	"paradise--fresh flowers, fragrant herbs and green trees.\n");
    add_item("oaks", 
        "The oak trees are old and magnificent of stature.\n");
    add_item("larches",
	"The larch trees are tall and green, reaching even higher "+
        "than the oaks.\n");
    add_item("bushes", 
        "The undergrowth consists chiefly of broad-leaved bushes.\n");
    add_item("shrubberies",
	"Green shrubberies with small flowers grow among "+
        "the broad-leaved bushes.\n");
    add_item(({"ground", "undergrowth", "underbrush"}),
        "The ground is overgrown with flowers, herbs and bushes.\n");
    add_item(({"flowers", "herbs"}),
	"The flowers and herbs give the air a sweet fresh fragrance.\n");

    add_cmd_item( ({ "air", "flowers", "herbs" }),
	    ({ "smell", "sniff", "inhale" }),
	    "The air is sweet with the fragrance of the flowers and herbs.\n");

    add_exit(ITH_DIR+"forest/edge1","north", 0, 2);

    BEACH
    add_prop(OBJ_I_CONTAIN_WATER, 100000);
    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")),
                     HERB_DIR + "attanar", HERB_DIR + "curugwath", }),
                  ({"bushes","shrubberies","forest","flowers"}), 2);
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
