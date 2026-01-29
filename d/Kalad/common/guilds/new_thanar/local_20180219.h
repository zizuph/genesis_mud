#include "/d/Kalad/defs.h"

/* Pathname aliases */
#define PARENT           "/d/Kalad/common/guilds/new_thanar/"
#define LOG_DIR           PARENT + "logs/"
#define STDIR             PARENT + "std/"
#define RDIR              PARENT + "rooms/"
#define ARM               PARENT + "arm/"
#define WEP               PARENT + "wep/"
#define LIV               PARENT + "npc/"
#define SPELLS            PARENT + "spells/"
#define THANAR_STD_ROOM   STDIR  + "thanar_church_std"
#define THANAR_BALC_STD   STDIR  + "thanar_balcony_std"

#define GENSPECIALS       "/d/Genesis/specials/guilds/"

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
* Descriptive Defines for Cathedral  Main Floor Rooms 
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