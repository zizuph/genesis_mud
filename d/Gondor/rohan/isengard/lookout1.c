/*
 *     /d/Gondor/opus/rohan/isengard/lookout1.c
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

#define PATH_WAY     "/d/Gondor/rohan/isengard/isengate.c"
#define OFFICER_NPC  ISEN_DIR + "npc/isen_commander"

// Prototypes
string  describe();
string  pathdesc();
string  gtower();
string  orthanc();
string  ringdesc();
string  windowdesc();
string  skydesc();
string  stardesc();
void    reset_room();

//Global Variables
static object Officer;
        //Guard in room.

public void
create_isengard()
{
    set_short("lookout on top of the Isenwall");
    set_long(describe);
    
    add_item( ({"path", "pathway", "gates", "outer gates",
                "gate"}), pathdesc);
    add_item( ({"watch tower", "watch towers", "towers",
                "guard tower", "guard towers"}), gtower);
    add_item( ({"sky", "clouds", "cloud"}), skydesc);
    add_item( ({"star", "stars"}), stardesc);
    add_item( ({"window", "tower window", "glow",
                "glow of light"}), windowdesc);
    add_item( ({"black tower", "tower", "tall tower", "orthanc",
                "outline", "structure", "tower-like structure",
                "pinnacle", "shape", "spikes", "spike"}), orthanc);
    add_item( ({"volcanic ring", "ring", "cliffs", "slope", "ringwall",
                "steep cliffs", "steep cliff", 
                "volcanic ringwall"}), ringdesc);
    add_item( ({"wall", "walls"}), BSN(
        "Standing about three feet high, the wall was constructed as a "+
        "safety measure to prevent anyone from falling off the lookout."));
    add_item( ({"floor", "ground"}), BSN(
        "The floor is fairly smooth and allows travel from one end of "+
        "the lookout to the other with greater ease and safety."));
    add_item( ({"isengard", "fortress", "vast fortress"}), BSN(
        "The expanse of Isengard extends around you as a vast fortress "+
        "ringed by the steep cliffs of the ringwall."));
    add_item( "lookout", BSN(
        "This area of the ringwall has been smoothed enough to allow "+
        "guards to walk on. Two watch towers are "+
        "used with the lookout to aid in the early detection of any "+
        "possible threats to Isengard."));
    add_item( ({"rock", "black rock", "smooth rock", 
        "smooth black rock"}), BSN(
            "This strange black rock makes up the entire ringwall. "+
            "It has been carved and shaped to form a walkway across "+
            "the top of the ringwall."));
    
        

    add_exit(ISEN_DIR + "lookout2.c", "north", 0);
    add_exit(ISEN_DIR + "wtower1.c",  "west", 0);
    add_exit(ISEN_DIR + "wtower2.c",  "east", 0);

    reset_room();
}

void
reset_room()
{
    Officer = clone_npc(Officer, OFFICER_NPC);
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
    string desc,time;
    
    time = tod();
    
    desc = "This is the top of the volcanic ring at the end of "+ 
        "what appears to be a lookout used to aid in the protection of "+
        "Isengard. Two watch towers rise above the lookout on either side. ";
    switch (tod())
    {
    case "night":
        desc += "The darkness from night greatly effects the ability "+
            "to see the surrounding area. In the distance, the outline of a "+
            "tall, tower-like structure can faintly be made out which "+
            "has been constructed within the volcanic ring. Just below is "+ 
            "the pathway that leads up to the outer gates of the tunnel. "+
            "The lookout continues off to the north.";
        break;
    case "early morning":
    case "morning":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. Through the "+time+" mist, on the horizon to the "+
            "north, the rough shape of a tall, black tower can be made out. "+
            "Just below, a long pathway can be seen leading up to the "+
            "outer gates. The lookout continues off to the north.";
        break;
    case "noon":
        desc += "The noontime sun is high in the sky allowing a perfect "+
            "view of the surroundings from here. On the horizon, to the "+
            "north, the rough shape of a tall, black tower can be made out. "+
            "Just below, a long pathway can be seen leading up to the "+
            "outer gates. The lookout continues to the north.";
        break;
    case "afternoon":
    case "evening":
        desc += "The "+time+" sun casts shadows across the land around "+
            "Isengard. On the horizon, to the north, the rough shape of a "+
            "tall, black tower can be made out. Just below, a long "+
            "pathway can be seen leading up to the outer gates. The "+
            "lookout continues off to the north.";
        break;
    default:
        desc += "Something is wrong, please notify a wizard!";
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
    string pdesc;
    object *lnames;

    switch (tod())
    {
        case "night":
            pdesc = "The darkness from night prevents a "+
                "good view of the pathway. Through the calm night, "+
                "movement and occasional mumbling from can be heard from "+
                "below, as well as the glow from a hand-held lantern.";
            break;
        default:
            pdesc = "Looking down, the pathway leading up to the outer "+
                "gates at the tunnel's entrance can be seen. ";
            seteuid(getuid(TO));
            (PATH_WAY)->load_me();
            lnames = FILTER_LIVE(all_inventory(find_object(PATH_WAY)));
            if (sizeof(lnames)>0) pdesc += "Currently "+
                COMPOSITE_LIVE(lnames)+" can be spotted on the pathway.";
            else pdesc += " Currently there is no one before the gates.";
            break;
    }

    return BSN(pdesc);
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
            tdesc = "Through the night air, the rough outline "+
                "of two guard towers, one on each side of the lookout, are "+
                "barely visible.";
            break;
        default:
            tdesc = "The watch towers are one either side of the lookout. "+
                "They appear to be just large enough for only a few people "+
                "to be inside at a time without being uncomfortable. The "+
                "towers are used by archers while defending Isengard from "+
                "attacks.";
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
            odesc = "Through the darkness, the outline of a tall, "+
               "tower-like structure can be seen. A glow of light from "+
               "some type of light source seems to be escaping through "+
               "a window of the tower.";
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
                "is a rough shape and the fact that it stretches into the "+
                "night.";
            break;
        default:
            rdesc = "The volcanic ring stretches around Isengard to aid "+
                "in the protection of the Tower of Orthanc. It appears to "+
                "have been made from existing rock and stands roughly one "+
                "hundred feet above the ground. From the looks of the steep "+
                "slope, it is probably almost impossible for anyone to "+
                "successfully scale the ringwall.";
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
                "of some type in the shadows before you.";
            break;
        default:
            windowd = "From here you cannot see any windows.";
            break;
    }
    return BSN(windowd);
}
           
