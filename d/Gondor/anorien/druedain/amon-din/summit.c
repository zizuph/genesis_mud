/*
 *  This is summit.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"  /* included for def RQ_STAGE_WAR */

#define HARD_TO_CLIMB 30 /* Miminum difficulty to climb drainpipe */
#define AWARE_NEEDED    25
#define DISCOVERED_DRAIN    "_gondor_i_found_din_drain"

void
create_room()
{
    set_south(1);

    add_view("Here on the edge of this summit, the view is clear"
           + " and unobscured in most directions.");

    set_short("near a small building atop the summit of Amon Din");
    set_long("@@describe");

    add_item(({"clasp","clasps"}), "@@exa_clasps");
    add_item(("building"), BSN(
      "The building is crafted of stone masonry, and looks very strong. " +
      "Its walls are long and mostly bare, giving little indication as " +
      "to what might be contained within. The roof is slanted slightly, " +
      "with tight shingles comprising its surface. The north face of " +
      "the building rests directly in front of you here."));
    add_item(({"face","stone","wall","walls","roof"}), "@@exa_wall");
    add_item(({"drain","drainpipe"}), "@@exa_drain");
    add_item(({"summit","surface","crest","hilltop","hill"}), BSN(
       "The trees and indeed even most of the grass has ceased to grow "
     + "upon the peak of this hill. Underfoot here and across the "
     + "entire summit, bare rock extends to form a leveled plateau."));
    add_item(({"rock","plateau"}), BSN(
       "Few plants grow on this rough surface. Undoubtedly, animal "
     + "life is sparse as well."));
    add_item(({"path","paths","slender path"}), BSN(
        "This path is well trodden from years of patrol and duty. It"
      + " winds down the slope to the north, or can be followed to"
      + " the south."));
    add_item(({"sky","stars","sun","sunlight"}), "@@sky");
    add_item(("tower"), "@@exa_tower");

    add_exit(AMON_DIR + "ad4","north");
    add_exit(AMON_DIR + "summit2","south");
}


string
sky()
{
    string  ld = "The sky above opens like a vast canopy.";
    switch(tod())
    {
        case "evening":
        case "night":
        case "early morning":
            ld += (" The stars peek through the darkness, illuminating the surroundings"
                + " with their twinkling essence.");
            break;
        default:
            ld += " Many of the clouds have retreated eastward,"
                + " allowing for ample sunlight to wash over this hilltop.";
            break;
    }
    return BSN(ld);
}

string
describe()
{
    string ld = "This summit commands a splendid view of the entire region.",
           time = tod();

    switch(time)
    {
        case "evening":
        case "night":
        case "early morning":
            ld += " Darkness has descended upon the "+time+" sky, and"
                + " the land flows in all directions as a sea of shadow"
                + " beneath the silent stars.";
            break;
        default:
            ld += " Shining brightly overhead, the "+time+" sun warms"
                + " the hilltop and allows for a detailed view of the"
                + " surrounding countryside for many miles.";
            break;
    }
    ld += " Built into the rock which forms the surface of this crest,"
        + " a long and narrow stone building runs southward across the"
        + " entire hilltop. Beside the building, and directly south"
        + " from here, the worn path winds beside a slender tower which"
        + " rises skyward. The path leads down the slope to the north.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += " Flames leap from atop the tower. The beacon signal has been lit!";
    }
    return BSN(ld);
}

string
exa_wall()
{
    string wtxt;
    wtxt = "This, the northern face of the building, is perhaps 15 feet tall, "
         + "and composed of large and smooth stone.";
    if (TP->query_skill(SS_AWARENESS) > AWARE_NEEDED)
    {
        wtxt += " You notice that a drainpipe, painted a color similar to that "
              + "of the stone, runs up the west side of this wall to the roof.";
        TP->add_prop(DISCOVERED_DRAIN,1);
    }
    return BSN(wtxt);
}

string
exa_drain()
{
    if (TP->query_prop(DISCOVERED_DRAIN))
    {
        return "It runs up to the roof and is attached to the wall by numerous clasps.\n";
    }
    else
        return "You cannot see any drainpipe here.\n";
}

int
climb_up(string str)
{
    object *others;
    int     i,
            diff,
            climb = TP->query_skill(SS_CLIMB);

    diff = random(HARD_TO_CLIMB)+25;

    if (!strlen(str) || (str != "drain" && str != "drainpipe"))
    {
        NF("Climb what?\n");
        return 0;
    }
    if (!TP->query_prop(DISCOVERED_DRAIN))
    {
        NF("You cannot see anything to climb up.\n");
        return 0;
    }
    others = FILTER_PLAYERS(all_inventory(TO));
    while (i < sizeof(others))
    {
        others[i]->add_prop(DISCOVERED_DRAIN,1);
        i++;
    }
    
    if (climb < diff)
    {
        write("You attempt to climb up the drainpipe, but your fingers cannot find \n");
        write("any good holds, and you remain on the ground.\n");
        say(QCTNAME(TP) + "fumbles with something along the wall.\n");
        return 1;
    }

    write("Grasping the drainpipe firmly, you scale the wall and climb onto the roof.\n");
    TP->move_living(" up the side of the wall",AMON_DIR + "roof1",1,0);
    return 1;
}

string
exa_tower()
{
    string ttxt;

    ttxt = "The diameter of this tower is actually quite narrow, measuring "
         + "perhaps 12 feet in width. The circular shaft which comprises its "
         + "base rises at least 50 feet into the air, and supports what "
         + "appears to be a large basin.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ttxt += " Bright flames rise from this basin, signifying that the "
              + "city of Minas Tirith is calling to its allies for aid. ";
    }

    return BSN(ttxt);
}

string
exa_clasps()
{
    if (TP->query_prop(DISCOVERED_DRAIN))
    {
        return("They hold the drainpipe firmly to the wall.\n");
    }
    else
        return("You see no clasps.\n");
}

void
init()
{
    ::init();
    add_action(climb_up, "climb");
}
