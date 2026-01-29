/*
 *  /d/Gondor/anorien/road/rroad8.c
 *
 *  Coded by Elessar.
 *
 *  Modification log:
 *  30-Jan-1997, Olorin:      Changed inheritance.
 *  9-April-2004, Tigerlily:  Added exit for new rangers
 *                            
 */
inherit "/d/Gondor/common/lib/area_room.c";

#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../../rangers.h"

string see_ranger_exit();
int ranger_exit();

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("You are standing just outside the ruins of Osgiliath. " +
        "The road runs south along the river and north into the city. It " +
        "is joined by another road coming from the west, trees lining it " +
        "on both sides. Disused streets run among the remains of tall " +
        "stone buildings long corrupted by wind and weather.");
    
    add_item("trees", "Trees line the road, but many of them have been " +
        "damaged by the effects of war, with broken limbs and no leaves.\n");
    add_item(({"buildings", "building"}), "Among the collapsed and destroyed " +
        "buildings that used to be Osgiliath, you see a partially intact " +
        "house to the east.\n");
    add_item("house", "A house stands partially intact to the east, although " +
        "only two walls remain standing, and these are blackened from fire.\n");

    add_item(({"streets", "street", "disused streets"}), &see_ranger_exit());
    add_exit(RANGERS_ITH_TUNNEL + "ruins_street", "east", &ranger_exit(),
        0, 1);
    add_exit(OSG_DIR + "wosg1",       "north", 0, 0);
    add_exit(ANO_DIR + "road/rroad7", "south", 0, 0);
    add_exit(ANO_DIR + "road/or5",    "west",  0, 0);
}

string
query_dir_to_gate()
{
    return "west";
}

string
see_ranger_exit()
{
    if (!RANGERS_FULL_MEMBER(TP))
    {
        return "The streets are covered with blackened rubble " +
            "and have large potholes. Clearly this is a war " +
            "zone.\n";
    }
    //else
    return "The streets are blackened with scorched rocks " +
        "and contain large potholes. However, your trained eyes " +
        "notice that tracks lead to the east into a small unused " +
        "street.\n";
}

int
ranger_exit()
{
    object tp = this_player(), *others = ({});
    int non_ranger_flag, num_in_room, i;

    non_ranger_flag = 0;
    if (!RANGERS_FULL_MEMBER(tp))
    {
        write("There is no obvious exit east.\n");
        return 1;
    }
    // else check for others in room
    others = FILTER_IS_SEEN(tp, all_inventory(this_object()));
    num_in_room = sizeof(others);

    for (i = 0; i < num_in_room; i++ )
    {
        // set flag for non-rangers in room
        // who can see ranger
        if (!RANGERS_FULL_MEMBER(others[i]))
        {
            non_ranger_flag = 1;
        }
    }
    //account for this_player = 1 in room and non-rangers present;)
    if (non_ranger_flag)
    {
        write("You cannot access the street " +
            "while you are being watched by non-rangers. " +
            "It must remain secret!\n");
        return 1;
    }
    //else
    return 0;
}

