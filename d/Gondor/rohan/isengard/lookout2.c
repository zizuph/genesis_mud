/*
 *     /d/Gondor/rohan/isengard/lookout2.c
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


// Prototypes
string  describe();
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
    
    add_item( ({"black tower", "tower", "tall tower", "orthanc",
                "outline", "structure", "tower-like structure",
                "pinnacle", "tall structure", "spike", "spikes",
                "tower of orthanc"}), orthanc);
    add_item( ({"towers", "guard tower", "guard towers", "watch tower",
                "watch towers"}), gtower);
    add_item( ({"volcanic ring", "ring", "ringwall", "slope", "cliffs",
                "cliff", "steep cliff", "steep cliffs",
                "volcanic ringwall"}), ringdesc);
    add_item( ({"star", "stars"}), stardesc);
    add_item( ({"window", "tower window", "glow",
                "glow of light"}), windowdesc);
    add_item( ({"wall", "walls"}), BSN(
        "Standing about three feet high, the wall was "+
        "constructed as a safety measure to prevent people from falling "+
        "off the lookout."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor is fairly smooth and allows travel from one end of "+
        "the lookout to the other with great ease and safety."));
    add_item( ({"stairs", "staircase"}), BSN(
        "Through an opening in the floor, these stairs lead down "+
        "into the depths of the volcanic ring tunnel somewhere below. The "+
        "darkness of the staircase prevents much more from being seen."));
    add_item( ({"isengard", "fortress", "vast fortress"}), BSN(
        "The expanse of Isengard extends about as a vast fortress "+
        "ringed by the steep cliffs of the ringwall."));
    add_item( "lookout", BSN(
        "This area of the ringwall that has been "+
        "smoothed enough to allow guards to walk on. Two towers at the south "+
        "end are used with the lookout to aid in the early detection of any "+
        "possible threats to Isengard."));
    add_item( ({"tunnel", "ring tunnel", "volcanic ring tunnel",
                "ringwall tunnel"}), BSN(
        "The tunnel that leads through the ringwall lies somewhere below, "+ 
        "probably reachable by decending the stairs."));
    add_item( ({"sky", "clouds", "cloud"}), skydesc);
    add_item( ({"rock", "black rock", "smooth rock", 
        "smooth black rock"}), BSN(
            "This strange black rock makes up the ringwall. "+
            "It has been carved and shaped to form a walkway across "+
            "the top of the ringwall."));

    add_exit(ISEN_DIR + "lookout3.c", "north", 0);
    add_exit(ISEN_DIR + "lookout1.c", "south", 0);
    add_exit(ISEN_DIR + "stair1.c",   "down",  0);
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
    
    desc = "This is the top of the volcanic ring in the middle of "+ 
        "what appears to be a lookout used to aid in the protection of "+
        "Isengard. "; 
    switch (tod())
    {
    case "night":
        desc += "The darkness from night greatly effects the ability "+
            "to see the surrounding area. In the distance, the outline of "+
            "a tall, tower-like structure can be seen, which has been "+
            "constructed within the volcanic ring. The lookout "+
            "continues to the north and the south, while a set of stairs "+
            "leads downward into the ringwall tunnel.";
        break;
    case "early morning":
    case "morning":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. Through the "+time+" mist, on the horizon to the "+
            "north, the rough shape of a tall, black tower can be made out. "+
            "The lookout continues to the north and south, while "+
            "a set of stairs leads downward into the ringwall tunnel.";
        break;
    case "noon":
        desc += "The noontime sun is high in the sky giving a perfect "+
            "view of the surroundings from here. On the horizon, to the "+
            "north, the rough shape of a tall, black tower can be seen. "+
            "The lookout continues to the north and south, while "+
            "a set of stairs leads downward into the ringwall tunnel.";
        break;
    case "afternoon":
    case "evening":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. On the horizon, to the north, the rough shape of a "+
            "tall, black tower is visible. The lookout continues "+
            "off to the north and south, while a set of stairs leads "+
            "downward into the ringwall tunnel.";
        break;
    default:
        desc += "Something is wrong, please notify a wizard!";
        break;
    }
    return BSN(desc);
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
            odesc = "Through the darkness, the outline of a tall, "+
               "tower-like structure can be made out. A glow of light "+ 
               "from some type of light source seems to be escaping "+
               "through a window of the tower.";
            break;
        default:
            odesc = "On the horizon, the Tower of Orthanc is visible"
                  + " stretching high above the volcanic ring. The"
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
                "is a rough shape and the fact that it stretches well "+
                "into the night.";
            break;
        default:
            rdesc = "The volcanic ring stretches around Isengard to aid "+
                "in the protection of the Tower of Orthanc. It appears to "+
                "have been made from existing rock and stands roughly one "+
                "hundred feet above the ground. From the looks of the steep "+
                "slope, it would be almost impossible for "+
                "anyone to scale the ringwall.";
            break;
    }
        
    return BSN(rdesc);
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
            windowd = "From here you cannot see any windows.";
            break;
    }
    return BSN(windowd);
}

string
gtower()
{
    string towerdesc;

    switch(tod())
    {
        case "night":
            towerdesc = "Darkness prevents a good look "+
               "at the guard towers. Through the night air they can be seen "+
               "rising high above the lookout.";
            break;
        default:
            towerdesc = "Just to the south, at the end of the lookout, "+
               "two watch towers rise high above the ringwall allowing "+
               "a good vantage point to spy any threats to Isengard.";
            break; 
    }  
    return BSN(towerdesc);
}
