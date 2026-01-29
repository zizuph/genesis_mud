/*
 *	/d/Gondor/ithilien/road/nr4.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include <language.h>

#include "/d/Gondor/defs.h"

public void reset_room();

static object  Harad_Captain;

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the crossroads " +
        "where this road meets the road from Osgiliath to Minas Morgul. Large " +
        "thickets and a tumbled land of rocky ghylls and crags lie to the east. " +
        "Behind them the long grim slopes of the Ephel Duath clamber up. To the " +
        "west, the forests of central Ithilien accompany the road. Sometimes the " +
        "Anduin can be seen through the top of the trees.\n");
    add_mountains(1, "only about a league");
    add_road(2);
    add_forest(1);
    add_exit(ITH_DIR + "road/nr5", "north", test_exit, 4);
    add_exit(ITH_DIR + "road/nr3", "south", test_exit, 4);

    set_alarm(90.0, 0.0, &reset_room());
}

public void
reset_room()
{
    object *harad_sol = allocate(5);
    object archer;
    
    if (!objectp(Harad_Captain))
    {
	Harad_Captain = clone_npc(Harad_Captain, 
				  ITH_DIR + "npc/haradcap");
	
	clone_npcs(harad_sol, ITH_DIR + "npc/haradstd", -1.0);
	archer = clone_npc(archer, ITH_DIR + "npc/harad_archer");

	archer->add_protectors(harad_sol);

	map(harad_sol, &Harad_Captain->team_join());
	Harad_Captain->team_join(archer);
    }
}

