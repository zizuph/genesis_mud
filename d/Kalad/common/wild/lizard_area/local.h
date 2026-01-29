/*
* Header file for the Saurian Area in Kalad
*
*/

#include "/d/Kalad/defs.h"

/* Pathname aliases */
#define PARENT           "/d/Kalad/common/wild/lizard_area/"
#define LOG_DIR           PARENT + "logs/"
#define STDIR             PARENT + "std/"
#define RDIR              PARENT + "rooms/"
#define ARM               PARENT + "arm/"
#define WEP               PARENT + "wep/"
#define OBJ               PARENT + "obj/"
#define LIV               PARENT + "npc/"
#define SPELLS            PARENT + "spells/"
#define DOORS             PARENT + "doors/"
#define LIZARD_STD_ROOM   STDIR  + "lizard_area_std"


#define GENSPECIALS       "/d/Genesis/specials/guilds/"
#define MIR_DEBUG(x)      find_player("mirandus")->catch_msg("[SAURIAN npc] " + x + "\n")

/*Room Defines */

#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
    "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])

/* 
* Descriptive Defines for Lizard Cave Rooms 
*/

#define LONG1 ({"The caverns expand into the darkness before you. ",\
"You stand within dark caverns deep beneath the harsh sun. ",\
"Beautifully established caverns expand before you. ",\
"The well-hewn walls, clearly made by hand, are well-established "\
+"but clearly ancient. ","You are within the caverns of some clearly "\
+"intelligent beings with an ancient history. ", "These caverns extend "\
+"deep beneath the lands of Kalad. ", "The caverns before you appear more "\
+"ancient than the lands of Kald themselves. ", "Caverns like those before "\
+"you are uncommon and not formed naturally. "})

#define LONG2 ({"The rough hewn walls rise higher than you would expect "\
+"and are domed at the top. ","The walls appear to be made of some black stone that "\
+"is reminsicent of the marble used in the City of Kalad. ","The domed "\
+"ceilings rise before you drawing your gaze upwards. ",\
"Beautifully hewn pillars rise from the floor to the ceiling granting "\
+"support to room around you. ","The carverns weave and turn through the "\
+"dark underground. ", "The caverns are well laid out and weave in a set "\
+"pattern that was clearly well thought out. ", "These caverns seems a bit "\
+"odd and clearly are unnatural. ", "The area seems cleaner than it should "\
+"for an underground area. ", "The depths of these caverns are cleaner than "\
+"one would anticipate. "})

#define LONG3 ({"The floors have clearly been cared for and cleaned despite "\
+"some small pebbles.","Stalagmites and Stalagtites are omnipresent creating "\
+"the appearance of teeth.", "The caverns appear to be in a concentric circle "\
+"drawing one to the middle.", "Tools and weapons are placed sporadically and "\
+"in an organized manner at certain points along the walls.", "The entire "\
+"cavern system appears to be the epitome form and function.", "Chattering "\
+"is overheard throughout these caverns. Clearly there is life here.", "Much "\
+"of what is present shows clear signs of intelligence, but why no technology."})

