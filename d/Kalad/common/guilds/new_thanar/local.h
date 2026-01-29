#include "/d/Kalad/defs.h"

/* Pathname aliases */
#define PARENT           "/d/Kalad/common/guilds/new_thanar/"
#define LOG_DIR           PARENT + "logs/"
#define STDIR             PARENT + "std/"
#define RDIR              PARENT + "rooms/"
#define BALC              RDIR   + "balcony/"
#define BASE              RDIR   + "basement/"
#define ARM               PARENT + "arm/"
#define WEP               PARENT + "wep/"
#define OBJ               PARENT + "obj/"
#define LIV               PARENT + "npc/"
#define SPELLS            PARENT + "spells/"
#define DOORS             PARENT + "doors/"
#define THANAR_STD_ROOM   STDIR  + "thanar_church_std"
#define THANAR_BALC_STD   STDIR  + "thanar_balcony_std"
#define THANAR_BASE_STD   STDIR  + "thanar_basement_std"

#define GENSPECIALS       "/d/Genesis/specials/guilds/"
#define MIR_DEBUG(x)      find_player("mirandus")->catch_msg("[Thanar npc] " + x + "\n")

/*Room Defines */

#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
    "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])

/* 
* Descriptive Defines for Cathedral  Main Floor Rooms 
*/

#define LONG1 ({"You standing within the Cathedrals opulence. ",\
"You are standing amongst the long wood pews of the Thanarian Cathedral. ",\
"The sanctuary of the Thanarian Cathedral opens before you. ",\
"Black marble shimmers as you gaze upon the glorious sanctuary of the "\
+"Thanarian Order. ","The Cathedral of the Thanarian order shimmers with "\
+"glorious wealth and authority before you. "})

#define LONG2 ({"The domed ceilings of the Cathedral rise towards the "\
+"heavens above. ","The walls of pure black marble are lined with "\
+"beautifully designed lanterns. ","The flourishing arches of the domed "\
+"ceiling rise before you drawing your gaze upwards to the sky. ",\
"Beautifully hewn pillars rise from the floor to the heavens granting "\
+"support to room around you. ","The span of the large room within which "\
+"you stand is inspiring. ", "It is apparent that this order has amassed "\
+"a great deal of wealth and much of it has gone into this Cathedral. "})

#define LONG3 ({"The black marble floors and walls are buffed to a "\
+"glorious shine.","Wooden pews expand out providing ample seating for "\
+"the patrons of the Cathedral.", "The sanctum and altar of the Cathedral "\
+"can be seen in the middle of the sanctuary.", "Wooden pews, designed "\
+"out a beautifully rich wood and fill much of the open space.", "The entire "\
+"Cathedral appears to be the epitome of opulence and wealth."})

/* 
* Descriptive Defines for Cathedral Balcony Rooms 
*/

#define BALC_LONG1 ({"You standing within the Cathedrals opulence. ",\
"You are on the balcony above the main level of the Thanarian Cathedral. ",\
"The sanctuary of the Thanarian Cathedral rests below you. ",\
"Black marble shimmers as you gaze upon the glorious sanctuary of the "\
+"Thanarian Order from you vantage above it. ","The Cathedral of the "\
+"Thanarian order shimmers with glorious wealth and authority below you. "})

#define BALC_LONG2 ({"The domed ceilings of the Cathedral rise towards the "\
+"heavens above. ","The walls of pure black marble are lined with "\
+"beautifully designed lanterns. ","The flourishing arches of the domed "\
+"ceiling rise before you drawing your gaze upwards to the sky. ",\
"Beautifully hewn pillars rise from the floor to the heavens granting "\
+"support to room around you. ","The span of the large room within which "\
+"you stand is inspiring. ", "It is apparent that this order has amassed "\
+"a great deal of wealth and much of it has gone into this Cathedral. "})

#define BALC_LONG3 ({"The black marble floors and walls are buffed to a "\
+"glorious shine.","Wooden rest along the balcony and provide ample seating for "\
+"the patrons of the Cathedral.", "The sanctum and altar of the Cathedral "\
+"can be seen in the middle of the sanctuary.", "Wooden pews, designed "\
+"out a beautifully rich wood and fill much of the open space below.", \
"The entire Cathedral appears to be the epitome of opulence and wealth."})

/*
* Descriptive Defines for Cathedral Basement Rooms
*/


/*
* Descriptive Defines for Cathedral Basement Rooms
*/

#define BASE_LONG1 ({"The basement of the Cathedral stands in sharp contrast "\
+"to the beauty and splendor of the main floor. ", "The basement is dark and "\
+"dank in comparison to the open splendor of the main level. ", "The air is "\
+"stale and smells of blood and sweat, a sharp contrast to the floors above. ",\
"The marble floors have no shimmer or shine when compared to those above and "\
+"it is obvious this is not a public space. "})

#define BASE_LONG2 ({"The ceiling, supported by wooden beams, is low and "\
+"and makes the space feel cramped. ", "The walls of the area are lined with "\
+"instruments of torture and the floors feel sticky from spilt blood. ",\
"The columns supporting the ceiling above and the lanterns attached to the "\
+"walls appear to have been added to this space. ","The walls and floor appear "\
+"to have been roughly installed, perhaps to cover something. "})

#define BASE_LONG3 ({"It is obvious from the design of this area that it "\
+"is used as a prison of sorts.", "The area is clearly used as a holding "\
+"area for prisoners that the Thanarians seek to question.", "It is apparent "\
+"from the surrounding area that this area is used to question prisoners "\
+"of the Thanarians.","There can be no doubt from this area that the "\
+"Thanarians are using creative methods to extract information."})
