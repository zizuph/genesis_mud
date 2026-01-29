/*
 *	/d/Gondor/ithilien/osgiliath/eosg5.c
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/osgiliath/eosg_std.c";

#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define SOLDIER  "/d/Gondor/minas/npc/gondor_soldier"
#define OFFICER  "/d/Gondor/minas/npc/gondor_officer"
#define RANGER   "/d/Gondor/common/npc/i_ranger"
#define ORC      "/d/Gondor/common/npc/reorc"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

public void reset_room();

static object  Npc1, Npc2, Npc3;

public void
create_area_room()
{
    set_areatype(0);
    set_areadesc("street");
    set_area("eastern");
    set_areaname("Osgiliath");
    set_land("Ithilien");
    set_extraline("You are standing in the east end of Osgiliath, with "
    + "old ruined stone buildings all around. A street leads through "
    + "the ancient city to the east. To the west the remains of a "
    + "stone bridge reach out partly across the river Anduin towards "
    + "the central isle of Osgiliath.");
    add_item("river", BSN("This is the river Anduin, which has its sources in the "+
			  "far north of Middle-earth."));
    add_item("forest", BSN(
    "The green forests of Ithilien look fair and inviting, "+
    "with great ilexes of huge girth, hoary ash-trees and giant oaks."));
    add_item(({"ruins","osgiliath","city"}), BSN(
    "The ruined city Osgiliath is uninhabited, its empty streets and "+
    "houses witnessing of a time long gone; of peace and thriving trade. "+
    "A street runs east out of the city."));

    add_exit(ITH_DIR + "osgiliath/eosgbridge", "west",  0, 1);
    add_exit(ITH_DIR + "osgiliath/nosg1",      "north", 0, 2);
    add_exit(ITH_DIR + "osgiliath/eosg2",      "east",  check_allow, 2);

    reset_room();

    BLACK_RIDER_ROOM->load_me();
}

private void
add_stuff()
{
    int     stage = rq_stage();
    string  npc_file;

    if (stage >= RQ_OSGILIATH_FIXED)
	npc_file = RANGER;
    else if (stage >= RQ_OSGILIATH_BROKEN)
	npc_file = ORC;
    else
	npc_file = SOLDIER;
    if (!objectp(Npc1)) 
    {
	Npc1 = clone_npc(Npc1, npc_file);
        Npc1->add_name("_stopping_npc");
    }
    if (!objectp(Npc2)) 
    {
	Npc2 = clone_npc(Npc2, npc_file);
        Npc2->add_name("_stopping_npc");
    }

    if (!objectp(Npc3)) 
    {
	if (stage < RQ_OSGILIATH_BROKEN)
	    npc_file = OFFICER;
	Npc3 = clone_npc(Npc3, npc_file);
        Npc3->add_name("_stopping_npc");
    }
}

public void
reset_room()
{
    set_alarm(1.0, 0.0, add_stuff);
}

public void
replace_npcs()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
    {
	set_alarm(10.0, 0.0, replace_npcs);
	return;
    }

    if (objectp(Npc1))
	Npc1->remove_object();
    if (objectp(Npc2))
	Npc2->remove_object();
    if (objectp(Npc3))
	Npc3->remove_object();

    reset_room();
}
