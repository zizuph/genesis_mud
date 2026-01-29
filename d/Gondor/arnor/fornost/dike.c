/*
 *      /d/Gondor/arnor/fornost/dike.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 *      29-Apr-2002, Finwe of the Shire, to match with 
 *      Bree recode of Old North Road
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    set_short("the Deadmen's Dike");

    add_grass();

    add_item("dike", BSN(
    "The dike is all that is left of the outer defence of the fortress. "+
    "In the last battle of Fornost, it was filled with so many corpses that "+
    "it's now known as the Deadmen's Dike."));
    add_item("ruins", BSN(
    "In the small valley lying between the southern hills of the North " +
    "Downs once must have stood a mighty fortress. All that is left now " +
    "are the overgrown ruins of wide walls, great halls, and many homes."));
    add_item(({ "greenway", "road", "ground", "highway"}), BSN(
    "The highway is the northern part of the Greenway, which in the old " +
    "days was built by the men of Gondor and Arnor to connect the two " +
    "kingdoms. It runs from the Gap of Rohan to the ruins of Fornost "+
    "lying north of the dike. Since Arnor has fallen and is already " +
    "almost forgotten, the road has fallen into disrepair and is " + 
    "overgrown. "));

    add_exit(FORNOST_DIR + "gate", "north", 0, 3);
    add_exit(ARNOR_DIR + "greenway/nr5", "south", 0, 2);
}

string
set_arnor_long()
{
    string desc;

    desc = "A grass covered stone road over a long dike. "+
    "The dike goes in a northwestern-southeastern direction. "+
    "The fallen ruins of ancient Fornost lie to the north, south the "+
    "Greenway goes to Bree. ";
    desc += query_arnor_time();

    return BSN(desc);
}
