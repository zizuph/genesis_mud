/*
 *     /d/Gondor/rohan/isengard/lookout3.c
 *
 *     Opus, April 1997
 *
 *     Copyright   1997 by Robert Miller
 *
 *     Modification log:
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;
                  
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define PATH_WAY   "/d/Gondor/rohan/isengard/ringrd1.c"

// Prototypes
int     block_mortal();
string  describe();
string  pathdesc();
string  orthanc();
string  ringdesc();
string  skydesc();
string  stardesc();
string  windowdesc();
string  gtower();

public void
create_isengard()
{
    set_short("lookout on top of the Isenwall");
    set_long(describe);
    
    add_item( ({"walk", "walkway", "gates", "inner gate",
                "inner gates", "gate", "road"}), pathdesc);
    add_item( ({"sky", "clouds", "cloud"}), skydesc);
    add_item( ({"black tower", "tower", "tall tower", "orthanc",
                "outline", "structure", "tower-like structure",
                "pinnacle", "tower of orthanc", "tall structure",
                "spikes", "spike"}), orthanc);
    add_item( ({"volcanic ring", "ring", "ringwall", "cliff", "cliffs",
                "steep cliff", "steep cliffs", "slope", 
                "volcanic ringwall"}), ringdesc);
    add_item( ({"wall", "walls"}), BSN(
        "Standing about three feet high, the wall was "+
        "constructed as a safety measure to prevent people from falling "+
        "off the lookout."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor is fairly smooth and allows travel from one end of "+
        "the lookout to the other with great ease and safety."));
    add_item( ({"stairs", "staircase"}), BSN(
        "Built right into the ringwall, the stairs lead downward "+
        "to the road below."));
    add_item( ({"isengard", "fortress", "vast fortress"}), BSN(
        "The expanse of Isengard extends about as a vast fortress "+
        "ringed by the steep cliffs of the ringwall."));
    add_item( "lookout", BSN(
        "This of the ringwall has been "+
        "smoothed enough to allow guards to walk on. Two guard towers, "+
        "located to the south, are used with the lookout to aid in the "+
        "early detection of any possible threats to Isengard."));
    add_item( ({"tunnel", "ring tunnel", "volcanic ring tunnel"}), BSN(
        "The tunnel that leads through the ringwall lies somewhere below."));


    add_exit(ISEN_DIR + "lookout2.c", "south",  0);
    add_exit(ISEN_DIR + "ringrd3.c", "stairs", block_mortal);
}

/* 
 *  Function name:  describe
 *  Description:    returns a time dependent description for
 *                  the room based on tod.
 *  Returns:        the room's long desc
 */

string
describe()
{   
    string desc, time;
    
    time = tod();
    
    desc = "This is the top of the volcanic ring at the end of "+ 
        "what appears to be a lookout used to aid in the protection of "+
        "Isengard. "; 
    switch (tod())
    {
    case "night":
        desc += "The darkness from night greatly effects visibility "+
            "of the surrounding area. In the distance, the outline of a "+
            "tall, tower-like structure can be seen which has been "+
            "constructed within the volcanic ring. Just below, a "+ 
            "walkway can be seen leading away from the inner gates. To the "+
            "east, a staircase leads down to a road below while the lookout "+
            "continues southward.";
        break;
    case "early morning":
    case "morning":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. Through the "+time+" mist, on the horizon to the "+
            "north, the rough shape of a tall, black tower is visible. "+
            "Just below, a walkway can be seen leading away from the "+
            "inner gates. To the east, a staircase leads down to a road "+
            "below while the lookout continues southward.";
        break;
    case "noon":
        desc += "The noontime sun is high in the sky giving a perfect "+
            "view of the surroundings from here. On the horizon, to the "+
            "north, the rough shape of a tall, black tower is visible. "+
            "Just below, a walkway can be seen leading away from the "+
            "inner gates. To the east, a staircase leads down to a road "+
            "below while the lookout continues southward.";
        break;
    case "afternoon":
    case "evening":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. On the horizon, to the north, you can make out "+
            "the rough shape of a tall, black tower. Just below, a "+
            "walkway can be seen leading up to the inner gates. To the "+
            "east, a staircase leads down to a road below while the "+
            "lookout continues off to the south.";
        break;
    default:
        desc += "This is not working right, please tell a wizard!";
        break;
    }
    return BSN(desc);
}

/*
 * Function name: pathdesc
 * Description:   returns a description of the room below (isengate.c)
 *                as well as any living thing that happen to be there.
 * Returns:       description of isengate.c and any living things that
 *                are also in the room at the time (NPCs or PCS).
 */

string
pathdesc()
{
// Remove this when the ringroad gets coded
    
    return BSN(
        "All that is visible at the moment is a roadway that may "+
        "eventually lead closer to Orthanc.");

/*
    string pdesc;
    object *lnames;

    switch (tod())
    {
        case "night":
            pdesc = "The darkness from night prevents a "+
                "good view of the pathway below. Through the calm night, "+
                "movement and occasional mumbling can be heard from below "+
                "and a faint glow from a small lantern can be seen.";
            break;
        default:
            pdesc = "Looking down, a clear view of the walkway "+
                "that leads from the inner gates to the Tower of Orthanc "+
                "is visible. The walkway is lined with pillars on both "+
                "sides. ";
            seteuid(getuid(TO));
            (PATH_WAY)->load_me();
            lnames = FILTER_LIVE(all_inventory(find_object(PATH_WAY)));
            if (sizeof(lnames)>0) pdesc += "Currently "+
            COMPOSITE_LIVE(lnames)+" can be seen below.";
            else pdesc += " Currently there is no one before the gates.";
            break;
    }

    return BSN(pdesc);
*/
}

/*
 * Function name: gtower 
 * Description:   gives a time dependent description to the guard towers
 * Returns:       a desc of the guard towers
 */

string
gtower()
{
    string tdesc;
    
    switch (tod())
    {        
        case "night":
            tdesc = "Darkness prevents a good look "+
               "at the guard towers. Through the night air they can be seen "+
               "rising high above the lookout.";
            break;
        default:
            tdesc = "Just to the south, at the end of the lookout, "+
               "two watch towers rise high above the ringwall allowing "+
               "a good vantage point to spy any threats to Isengard.";
            break; 
    }
    return BSN(tdesc);
}

/*
 * Function name: orthanc
 * Description:   gives the desc of the Tower of Orthanc if examined
 * Returns:       desc of Orthanc
 */

string
orthanc()
{
    string odesc;

    switch(tod())
    {
        case "night":
            odesc = "Through the darkness of night, the rough outline of "+
               "the Tower of Orthanc is visible. A faint glow from a torch "+
               "or lantern is escaping through a window.";
            break;
        default:
            odesc = "On the horizon, the Tower of Orthanc"
                  + " stretches high above the volcanic ring. The"
                  + " tower seems to have four sharp spikes creating"
                  + " a pinnacle at the very top.";
            break;
    }

    return BSN(odesc);
}

/*
 * Function name: ringdesc
 * Description:   gives the description of the ringwall if examined
 * Returns:       description of the ringwall
 */


string
ringdesc()
{
    string rdesc;
    
    switch (tod())
    {
        case "night":
            rdesc = "It is too dark to get a good look at the volcanic ring "+
                "that surrounds and protects Isengard. All that can make out "+
                "is a rough shape and the fact that it stretches well into "+
                "the night.";
            break;
        default:
            rdesc = "The volcanic ring stretches around Isengard to aid "+
                "in the protection of the Tower of Orthanc. It appears to "+
                "have been made from existing rock and stands roughly one "+
                "hundred feet above the ground. From the looks of the steep "+
                "slope, it would be almost impossible for anyone to scale "+
                "the ringwall.";
            break;
    }
        
    return BSN(rdesc);
}

/* 
 * Function:    block_mortal
 * Description: keeps mortals from using exit until further coding done
 * Returns:     1/0
 */

static int
block_mortal()
{
    if (TP->query_wiz_level())
    {    
        write("This exit is still closed for mortals, wizard.\n");
        return 0;
    }
    else 
    {
       write("A section of stairs is missing, preventing use of the stairs.\n");
       return 1;
    }
}

string
skydesc()
{
    string sdesc;

    switch(tod())
    {
        case "night":
            sdesc = "The night sky is full of stars that look like "+
               "tiny dots in the sky. Darkness is cast across the land "+
               "greatly hindering visibility.";
            break;
        case "early morning":
        case "morning":
            sdesc = "The early morning sun is just peeking over the "+
               "horizon casting shadows across the land. A few clouds "+
               "are visible in the sky.";
            break;
        case "noon":
            sdesc = "The noontime sun is high in the sky providing warmth "+
               "and light to the entire surrounding area. The sky looks "+ 
               "fairly clear with the exception of a distant cloud or two.";
            break;
        case "afternoon":
        case "evening":
            sdesc = "As the sun begins to decend and make its way to the "+
               "horizon to retire for the night, shadows begin to cross the "+
               "land. The radient colors from the setting sun paint the sky "+
               "and the clouds that are nearby.";
            break;
        default:
            sdesc = "Something is not right, please notify a wizard or make "+
               "a bug report.";
            break;
    }
    return BSN(sdesc);
}

string
stardesc()
{
    string stard;

    switch(tod())
    {
        case "night":
            stard = "Stars looking like tiny white dots fill the entire "+
                "sky above.";
            break;
        default:
            stard = "It is day so no stars can be seen.";
            break;
    }
    return BSN(stard);
}

string
windowdesc()
{
    string windowd;

    switch(tod())
    {
        case "night":
            windowd = "Light is radiating from a window of a structure "+
                "of some type in the distance.";
            break;
        default:
            windowd = "From here, no windows are visable.";
            break;
    }
    return BSN(windowd);
}

