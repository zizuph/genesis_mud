
/* Defines for standardised sailing code */

#define STD_CONTENTS_DESC  "/d/Krynn/std/boats/contents_desc"
#define STD_AHOY_CMD       "/d/Calia/std/ahoy"
#define STD_BOAT_OWNER     "/d/Calia/std/owner"

#define STD_BOAT_OUT       "/d/Krynn/std/boats/std_boat_out"
#define STD_BOAT_IN        "/d/Krynn/std/boats/std_boat_in"
#define STD_BOAT_ROOM      "/d/Krynn/std/boats/std_boat_room"

/* Require certain SS_ACROBAT skill to board other ships */
#define HARD_TO_JUMP       20

/* The default sailing skill used by Mariners, Minotaurs, and Pirates */
#define SAILING_SKILL      143020

/* Default number of boats to a room */
#define KRYNN_MAX_BOATS 30

/* Sailing skill difficulty level */
#define DIFFICULTY_NONE          0
#define DIFFICULTY_NOVICE        9
#define DIFFICULTY_LAYMAN        29
#define DIFFICULTY_JOURNEYMAN    49
#define DIFFICULTY_PROFESSIONAL  69
#define DIFFICULTY_MASTER        89
#define DIFFICULTY_GURU          99
#define NO_SAIL_DISABLED         998
#define NO_SAIL_ANCHORED         999

/* Ship sizes from smallest to largest */
#define SLOOP         1
#define CUTTER        2
#define SCHOONER      3
#define CORVETTE      4
#define FRIGATE       6
#define MAN_OF_WAR    8

/* Sailing conditions */
#define CONDITIONS_NORMAL             0
#define CONDITIONS_TRICKY             30
#define CONDITIONS_CHALLENGING        51
#define CONDITIONS_EXT_CHALLENGING    76
#define CONDITIONS_NEAR_IMPOSSIBLE    91

#define SAIL_DEBUG(x)  find_player("arman")->catch_msg("[Sailing] " + x + "\n")

/* Ship types for customisable ships at the Palanthas dry docks */

#define CUSTOM_SHIP_NAME ([ \
    "sloop" : ({ "fishing boat", "sloop" }), \
    "cutter" : ({ "cutter", "harbour pilot", "smuggler vessel", "pleasure yacht" }), \
    "schooner" : ({ "schooner", "brigantine" }), \
    "corvette" : ({ "corvette", "patrol boat", "sloop-of-war" }), \
    "frigate" : ({ "galley", "frigate", "galleon" }), \
    "man-o-war" : ({ "warship", "man-of-war" }) \
])

#define CUSTOM_SHIP_ADJ ([ \
    "sloop" : ({ "swift", "weathered", "barnacled", "trim", "well-made", "battered" }), \
    "cutter" : ({ "nimble", "trim", "well-made", "swift", "white-sailed", "elegant" }), \
    "schooner" : ({ "twin-sailed", "weathered", "sharply-built", "trim", "fast", "merchant" }), \
    "corvette" : ({ "sleek", "menacing", "quick", "battle-scarred" }), \
    "frigate" : ({ "powerful", "broad-decked", "grand", "imperial", "war", "slave" }), \
    "man-o-war" : ({ "commanding", "majestic", "towering"}) \
])

#define CUSTOM_SHIP_LONG_OUT ([ \
    "sloop" : ({ "A small fishing boat, commonly seen chasing the schools " + \
        "of fish that are common along the coastlines of Ansalon. ", \
        "A small sloop, a swift sailboat with a single mast rigged with " + \
        "a mainsail to the aft and a headsail rigged to the front. " }), \
    "cutter" : ({ "Before you is a sailing vessel known as a cutter, " + \
        "a medium-sized ship with a single mast, designed for speed rather " + \
        "than capacity. ", \
        "This medium-sized sailboat is a pilot boat common to harbours " + \
        "around Ansalon, renowned as a nimble yet capable heavy working " + \
        "boat. ", \
        "This single-masted sailing ship is a common smuggler's vessel - small " + \
        "enough to slip into a harbour unseen, fast enough to outrun local " + \
        "navy patrol boats, but with enough cargo space to ferry lucrative " + \
        "goods for a decent profit. ", \
        "This sleek single-masted sailing vessel is commonly owned by " + \
        "nobility or the rich. It is no working ship, designed for cruising " + \
        "or racing, with many creature comforts not afforded your usual sailor. " }), \
    "schooner" : ({ "A medium-sized vessel with two masts and rigged both " + \
       "fore and aft. This ship is commonly used as a merchant vessel, " + \
       "being fast and versatile for its size and requiring less crew than " + \
       "some of the square rig ships that ply the ocean. ", \
       "A medium-sized vessel with two masts fully square-rigged. " + \
       "While swift by sail, this ship is popular also for its ability to " + \
       "engage up to eight oars on each side, making it a favourite of " + \
       "merchants and pirates alike. " }), \
    "corvette" : ({ "This three masted square-rigged corvette is one of the " + \
       "smallest and fastest class of warships to sail the seas of Ansalon. " +\
       "Quick and maneuverable, it is well suited for patrolling or raiding. ", \
       "This is a three masted square-rigged naval patrol boat, one of the " + \
       "small corvette-class of warships that sail the seas of Ansalon. " +\
       "Quick and maneuverable, it is well suited for patrolling or raiding. ", \
       "This three masted vessel is a sloop-of-war, the smallest of the " + \
       "ships classed as warships. Unlike similar-sized warships, this " + \
       "vessel has the aft-most mast fore-and-aft rigged, allowing it to " + \
       "be incredibly maneuverable, even able to sail backwards! " }), \
    "frigate" : ({ "This long, slender-hulled vessel is a galley. While three " + \
       "masts allow sailing in favourable winds, this ship is primarily " + \
       "propelled by oars and manpower. ", \
       "This large ocean-going ship is a frigate, a warship used by navies " + \
       "to hunt pirates and protect merchant convoys. Three masts full-rigged " + \
       "with dual decks, this vessel is capable of carrying many sailors and " + \
       "marines swiftly across the sea. ", \
       "This large, multi-decked sailing ship is often used as an armed cargo " + \
       "carrier and converted to a warship in times of conflict. " }), \
    "man-o-war" : ({ "A monster of a ship rises out of the water before you. " + \
       "Four masts rigged with huge white sails rise high from the main deck, " + \
       "and you cannot help but marvel at this warship as it truly is " + \
       "magnificent to behold. Without a doubt this massive vessel " + \
       "would be the pride of any fleet, the flagship of admirals. Armed with " + \
       "a number of ballistas on both sides of the deck, this warship should be " + \
       "approached with caution at best. ", \
       "A monster of a ship rises out of the water before you. " + \
       "Four masts rigged with huge white sails rise high from the main deck, " + \
       "and you cannot help but marvel at this man-of-war as it truly is " + \
       "magnificent to behold. Without a doubt this massive vessel " + \
       "would be the pride of any fleet, the flagship of admirals. Armed with " + \
       "a number of ballistas on both sides of the deck, this man-of-war should be " + \
       "approached with caution at best. "}) \
])

#define CUSTOM_SHIP_LONG_IN ([ \
    "sloop" : ({ "You are sitting inside a small fishing boat. " + \
        "While nothing particularly special compared to the well-crafted ships " + \
        "of the minotaurs, or the elegant vessels piloted by the elves, it meets " + \
        "the purposes of any local fisherman. A single mast rises out of the " + \
        "middle of the deck, its billowing canvas sail unfurled, ready for swift " + \
        "sailing. ", \
        "You stand aboard a small sloop, a swift sailboat with a single mast " + \
        "rigged with a mainsail to the aft and a headsail rigged to the front. " }), \
    "cutter" : ({ "You stand aboard a sailing vessel known as a cutter, " + \
        "a medium-sized ship with a single mast, designed for speed rather " + \
        "than capacity. ", \
        "You stand aboard a pilot boat. Common to harbours " + \
        "around Ansalon, this ship is renowned as a nimble yet capable " + \
        "heavy working boat. ", \
        "You stand aboard a common smuggler's vessel. This ship is small " + \
        "enough to slip into a harbour unseen, fast enough to outrun local " + \
        "navy patrol boats, and with enough cargo space to ferry lucrative " + \
        "goods for a decent profit. ", \
        "You stand aboard a pleasure yacht, a vessel commonly owned by " + \
        "nobility or the rich. It is no working ship, but designed for cruising " + \
        "or racing, with many creature comforts not afforded your usual sailor. " }), \
    "schooner" : ({ "You stand aboard a medium-sized schooner, a vessel with " + \
       "two masts and rigged both " + \
       "fore and aft. This ship is commonly used as a merchant vessel, " + \
       "being fast and versatile for its size and requiring less crew than " + \
       "some of the square rig ships that ply the ocean. ", \
       "You stand aboard a brigantine, a medium-sized vessel with " + \
       "two masts fully square-rigged. " + \
       "While swift by sail, this ship is popular also for its ability to " + \
       "engage up to eight oars on each side, making it a favourite for " + \
       "merchants and pirates alike. " }), \
    "corvette" : ({ "You stand aboard a three masted square-rigged corvette, " + \
       "one of the " + \
       "smallest and fastest class of warships to sail the seas of Ansalon. " +\
       "Quick and maneuverable, it is well suited for patrolling or raiding. ", \
       "You stand aboard a three masted square-rigged naval patrol boat, one of the " + \
       "small corvette-class of warships that sail the seas of Ansalon. " +\
       "Quick and maneuverable, it is well suited for patrolling or raiding. ", \
       "You stand aboard a three masted sloop-of-war, the smallest of the " + \
       "ships classed as warships. Unlike similar-sized warships, this " + \
       "vessel has the aft-most mast fore-and-aft rigged, allowing it to " + \
       "be incredibly maneuverable, even able to sail backwards! " }), \
    "frigate" : ({ "You stand on deck of a long, slender-hulled galley. While three " + \
       "masts allow sailing in favourable winds, this ship is primarily " + \
       "propelled by oars and manpower. ", \
       "You stand on deck of a large ocean-going frigate, a warship used by navies " + \
       "to hunt pirates and protect merchant convoys. Three masts full-rigged " + \
       "with dual decks, this vessel is capable of carrying many sailors and " + \
       "marines swiftly across the sea. ", \
       "You stand aboard a large, multi-decked galleon, a ship that is " + \
       "often used as an armed cargo " + \
       "carrier and converted to a warship in times of conflict. " }), \
    "man-o-war" : ({ "You stand on the deck of a grand warship. " + \
       "Four masts rigged with huge white sails rise high from the main deck, " + \
       "and you cannot help but marvel at this warship as it truly is " + \
       "magnificent to behold. Without a doubt this massive vessel " + \
       "would be the pride of any fleet, the flagship of admirals. Armed with " + \
       "a number of ballistas on both sides of the deck, this warship should be " + \
       "approached with caution at best. ", \
       "You stand on the deck of a grand man-of-war. " + \
       "Four masts rigged with huge white sails rise high from the main deck, " + \
       "and you cannot help but marvel at this man-of-war as it truly is " + \
       "magnificent to behold. Without a doubt this massive vessel " + \
       "would be the pride of any fleet, the flagship of admirals. Armed with " + \
       "a number of ballistas on both sides of the deck, this man-of-war should be " + \
       "approached with caution at best. "}) \
])

/* Water defines as outlined in /d/Calia/sys/water.h */

#ifndef WATER_DEFS
#define WATER_DEFS

#define IN_WATER(player)  \
     (environment(player)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)

#define UNDER_WATER(player) \
     (environment(player)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)

#define IN_DEEP_WATER(player) \
     (IN_WATER(player) && stringp(environment(player)->query_sink_path()))
 
#define IN_SHALLOW_WATER(player) \
     (IN_WATER(player) && !(IN_DEEP_WATER(player)))
 
#define DROWN_OBJECT "/d/Calia/sea/objects/drown_ob" 
#define DROWN_OBJECT_NAME "drown_object"
 
#define MOBILITY_OBJECT "/d/Calia/sea/objects/mobility_ob" 
#define MOBILITY_OBJECT_NAME "mobility_object"
 
#define BOAT "/d/Calia/std/boat"
#define BOAT_IN "/d/Calia/std/boat_in"

#define MAX_BOATS_IN_ROOM 3
#define LIVE_I_GILLS "_live_i_gills"
#define LIVE_O_DROWN_OB "_live_o_drown_ob"
#define OBJ_I_FLOAT "_obj_i_float"
#define DROWN_HEARTBEAT 10

#define NO_SAY_UNDER_WATER "You cannot converse under water, you will "+\
                           "have to signal instead.\n"
#define NO_UNDER_WATER "You cannot do that under water.\n"

#endif

