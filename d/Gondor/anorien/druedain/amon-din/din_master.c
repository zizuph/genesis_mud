/*  The master file for the summit of Amon Din.
 * 
 *  Created by: Gorboth of Gondor,  July 1995
 *
 *  Special notes:  This file allows, among other things, a player to look
 *                  in different directions and see a nice view. Also 
 *                  included are variable obstacles in the switch. These are:
 *
 *                             1 = beacon tower
 *                             2 = large tree
 *                             3 = treetops
 *                             4 = building
 *
 *                  Rooms that inherit this file can select an obstacle for
 *                  a given direction the following way:
 *
 *                             set_north(1);  // tower prevents seeing north
 *                             set_west(3);   // treetops prevent seeing west
 *
 *                  Room specific text can be added to rooms like this:
 *
 *                             add_view("Boy, this room has a nifty view!");
 *
 *                  Special thanks to Olorin for helping on this project.
 *
 *  Revision history:
 */
inherit "/d/Gondor/common/room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

int    stage   = CLOCK->query_rq_stage();
string tower   = " The beacon tower prevents seeing in that direction.",
       tree    = " The large tree prevents seeing in that direction.",
       trees   = " The treetops prevent seeing in that direction.",
       build   = " The building prevents seeing in that direction.";

static int  north,
            east,
            south,
            west;

varargs void  set_north(int i = 1)		{ north = i; }
varargs void  set_east(int i = 1)		{ east = i; }
varargs void  set_south(int i = 1)		{ south = i; }
varargs void  set_west(int i = 1)		{ west = i; }

varargs void
add_view(string extra = "")
{
    add_item("view", "@@view|"+extra+"@@");
    add_item(({"north","north view","northern view"}), "@@n_view");
    add_item(({"east","east view","eastern view"}), "@@e_view");
    add_item(({"south","south view","southern view"}), "@@s_view");
    add_item(({"west","west view","western view"}), "@@w_view");
    add_item(("basin"), "@@exa_basin");
    add_item(({"sky","up"}), "@@exa_sky");
    add_item(({"star","stars"}), "@@exa_stars");
    add_item(("sun"), "@@exa_sun");
    add_item(({"summit","hill","hilltop","plateau"}), "@@exa_summit");
}

varargs string
view(string extra)
{
    string vv = "This summit commands an astounding view of the"
              + " surrounding countryside. The view is so expansive"
              + " that the only way to take it in properly is to look"
              + " in a single direction at once.";

    if (strlen(extra))
        vv += (" " + extra);
    return BSN(vv);
}

varargs string
n_view()
{
    string ntxt;

    switch(north)
    {
        case 0:
            ntxt = "The fields of Anorien stretch out to the north,"
		+ " running a great distance until they reach the shores"
		+ " of the mighty Anduin. Beyond that is barely visible"
		+ " the distant regions of northern Ithilien and the fens"
		+ " known as the Wetwang which border its western reaches."
		+ " The Great West Road runs directly north of this summit,"
		+ " rows of tall trees forming a green belt along its"
		+ " edges.";
            break;
        case 1:
            ntxt = "The view to the north seems obscured." + tower;
            break;
        case 2:
            ntxt = "The view to the north seems obscured." + tree;
            break;
        case 3:
            ntxt = "The view to the north seems obscured." + trees;
            break;
        case 4:
            ntxt = "The view to the north seems obscured." + build;
            break;
    }
    return BSN(ntxt);
}

varargs string
e_view()
{
    string etxt;

    switch(east)
    {
        case 0:
            etxt = "Bordered by its rows of tall trees, the Great West"
                + " Road turns south directly to the east as it makes"
                + " its way towards the great walled city. The Anduin"
                + " also winds to the south in that direction, and the"
                + " ruins of Osgiliath are visible upon its shores."
                + " Beyond the water can be seen the forests of northern"
                + " Ithilien which rest at the feet of the Ephel Duath."
                + " Above the grim peaks, all is dark.";
            break;
        case 1:
            etxt = "The view to the east seems obscured." + tower;
            break;
        case 2:
            etxt = "The view to the east seems obscured." + tree;
            break;
        case 3:
            etxt = "The view to the east seems obscured." + trees;
            break;
        case 4:
            etxt = "The view to the east seems obscured." + build;
            break;
    }
    return BSN(etxt);
}

varargs string
s_view()
{
    string stxt;

    switch(south)
    {
        case 0:
            stxt = "The Rammas Echor is visible to the south, its"
                + " westernmost corners melding tightly with the"
                + " foothills of the White Mountains. Continuing far"
                + " to the west, the peaks of the Ered Nimrais"
                + " dominate the southern horizon. Innumerable trees"
                + " crowd the feet of the mountain range, as the Greywood"
                + " merges with the Druadan forest, both running through"
                + " the Stonewain Valley.";
            break;
        case 1:
            stxt = "The view to the south seems obscured." + tower;
            break;
        case 2:
            stxt = "The view to the south seems obscured." + tree;
            break;
        case 3:
            stxt = "The view to the south seems obscured." + trees;
            break;
        case 4:
            stxt = "The view to the south seems obscured." + build;
            break;
    }
    return BSN(stxt);
}

varargs string
w_view()
{
    string wtxt;

    switch(west)
    {
        case 0:
            wtxt = "For a great length, the Druadan forest spreads to"
                + " the west, its grey and green foliage running beside"
                + " the feet of the Ered Nimrais. Beyond the forest, the"
                + " tall mountains continue for as far as the eye can see."
                + " Also trailing beyond the forest, and across the fields of"
                + " Anorien, the Great West Road is visible, its way marked"
                + " by green belts of trees on either side. Eilenach"
                + " and Nardol, sister hills to Amon Din, rise beyond"
                + " the treetops";
            if (stage >= RQ_STAGE_WAR)
            {
                wtxt += ", their beacons burning bright.";
            }
            else
                wtxt += ".";
            break;
        case 1:
            wtxt = "The view to the west seems obscured." + tower;
            break;
        case 2:
            wtxt = "The view to the west seems obscured." + tree;
            break;
        case 3:
            wtxt = "The view to the west seems obscured." + trees;
            break;
        case 4:
            wtxt = "The view to the west seems obscured." + build;
            break;
    }
    return BSN(wtxt);
}

varargs string
exa_basin()
{
    string btxt;

    btxt = "A basin rests high atop the peak of this tower. Very little"
         + " is evident from here as to what it might contain";

    if (stage > RQ_STAGE_WAR)
    {
        btxt += ", save for the flames which rise steadily from its"
              + " sides.";
    }
    else
        btxt += ".";

    return BSN(btxt);
}

varargs string
exa_sky()
{
    string time = tod(),
           skytxt = "Raising your eyes to the heavens, you see that";
           stage = CLOCK->query_rq_stage();

    if (stage < RQ_STAGE_WAR)
    {
        switch(time)
        {
            case "evening":
            case "night":
            case "early morning":
                skytxt += " the stars peek through the "+time
                  + " darkness, illuminating the surroundings with"
                  + " their twinkling essence.";
                break;
            default:
                skytxt += " most of the clouds have retreated"
                  + " eastwards, allowing the "+time+" sun to wash"
                  + " over this hilltop.";
                break;
        }
    }
    else
        skytxt += " dark and brooding clouds cover the entire sky."
                + " The oppresive weight of this dark canopy is"
                + " enough to dampen even the brightest optimism.";

    return BSN(skytxt);
}

varargs string
exa_stars()
{
    string time = tod(),
           star;
    int    stage = CLOCK->query_rq_stage();

    if (stage < RQ_STAGE_WAR)
        switch(time)
        {
            case "evening":
            case "night":
            case "early morning":
                star = "From this high vantage point the stars seem"
                     + " countless. You marvel at their delicate and"
                     + " yet powerful arrangement.";
                break;
            default:
                star = "Peering into the "+time+" sky, you search"
                     + " for signs of starlight, but find none.";
                break;
        }
    else
        star = "You gaze into the forboding cloud cover, searching"
             + " earnestly for any signs of the sky beyond, yet"
             + " there is only the swirling darkness.";

    return BSN(star);
}

varargs string
exa_sun()
{
    string time = tod(),
           sun;
    int    stage = CLOCK->query_rq_stage();

    if (stage < RQ_STAGE_WAR)
        switch(time)
        {
            case "evening":
            case "night":
            case "early morning":
                sun = "You gaze into the distant horizon, wondering"
                    + " how long you will need to wait to see the"
                    + " rising sun.";
                break;
            default:
                sun = "The "+time+" sun shines brightly overhead,"
                    + " spreading warmth and brilliance upon this"
                    + " hilltop.";
                break;
        }
    else
        sun = "You gaze into the forboding cloud cover, searching"
             + " earnestly for any signs of the sky beyond, yet"
             + " there is only the swirling darkness.";

    return BSN(sun);
}

varargs string
exa_summit()
{
    string s = "Aside from a small number of trees growing in specific"
             + " locations, this summit is devoid of any foliation."
             + " Below you here and across the entire hilltop, bare"
             + " rock extends to form a leveled plateau.";

    return BSN(s);
}
