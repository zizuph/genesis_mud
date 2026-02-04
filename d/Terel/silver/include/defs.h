/* 
 * Silver forest defs.h file
 * Tomas -- Aug. 2000
 * ->I've added defs similar to those existing in Krynn, I'm sorry I wrote, whole
 * lot of code using them before I realized they were local;] - Udana
 * ->I've added weapon directory definition.
 * ->I've added sanity check, how did ever go on with out it?! - Udana
 * ->I've added some definition for decryption quest.
 * ->I've added the define for the upcomming root system
 */

#ifndef SILVER_FOREST_NEW_DEFS
#define SILVER_FOREST_NEW_DEFS

#define DEFAULT    "/d/Terel/silver/"

#define MONSTER    DEFAULT + "monster/"
#define NPC        DEFAULT + "npc/"
#define OBJ        DEFAULT + "obj/"
#define ARMOUR     DEFAULT + "armour/"
#define WEAPON     DEFAULT + "weapon/"
#define FOREST     DEFAULT + "forest/"
#define FOREST_AG  DEFAULT + "forest_ag/"
#define FOREST_HP  DEFAULT + "forest_hp/"
#define FOREST_QZ  DEFAULT + "forest_qz/"
#define HAG        DEFAULT + "hag/"
#define HOVEL      HAG + "hovel"
#define ROAD       DEFAULT + "road/"
#define CARAVAN    DEFAULT + "caravan/"
#define ROOTS      DEFAULT + "roots/"

#define HOVEL_LOC_LOG  "/d/Terel/log/hag_hovel_location"
#define CAR_LOG "/d/Terel/log/caravan"
#define RED_DRAGON_LAIR "/d/Terel/mountains/redlair/cave01"

#define MAX_INSIDE_CARAVAN_WAGON 11

#define INCLUDE    DEFAULT + "include/"

#define HAG_LOCATIONS ({ \
    FOREST_AG + "forest_dd16" \
})

//Some Krynn borrowed definitions:

#define E(x) environment(x)
#define QVB query_verb()
#define SEND(x)    find_player("udana")->catch_msg( x + "\n" )

#define IS_CARAVAN_COACHMAN "_is_caravan_coachman"
#define ROUTE ({ROAD + "road02.c", ROAD + "road03.c", ROAD + "road04.c", \
ROAD + "road05.c", ROAD + "road06.c",\
ROAD + "road07.c", ROAD + "road08.c", ROAD + "road09.c", ROAD + "road10.c", ROAD + "road11.c",\
ROAD + "road12.c", ROAD + "road13.c", ROAD + "road14.c", ROAD + "road15.c", ROAD + "road16.c",\
ROAD + "road17.c", ROAD + "road18.c", ROAD + "road19.c", ROAD + "road20.c", ROAD + "road21.c",\
ROAD + "road22.c", ROAD + "road23.c", ROAD + "road24.c", ROAD + "road25.c", ROAD + "road26.c",\
ROAD + "road27.c", ROAD + "road28.c", ROAD + "road29.c", ROAD + "road30.c", ROAD + "road31.c",\
ROAD + "road32.c", ROAD + "road33.c", ROAD + "road34.c", ROAD + "road35.c", ROAD + "road36.c",\
ROAD + "road37.c", ROAD + "road38.c", ROAD + "road39.c", ROAD + "road40.c", ROAD + "road41.c",\
ROAD + "road42.c", ROAD + "road43.c", ROAD + "road44.c", ROAD + "road45.c", ROAD + "road46.c",\
ROAD + "road47.c", ROAD + "road48.c", ROAD + "road49.c", ROAD + "road50.c", ROAD + "road51.c",\
ROAD + "road52.c", ROAD + "road53.c", ROAD + "road54.c", ROAD + "road55.c", ROAD + "road56.c",\
ROAD + "road57.c", ROAD + "road58.c", ROAD + "road59.c", ROAD + "road60.c", ROAD + "road61.c",\
ROAD + "road62.c", ROAD + "road63.c"})

//Decryption definitions:

#define PASSWORD_SIZE 10
#define LETTERS ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"})
#define PLAYER_M_T_PASSWORD "_player_m_t_password"
#define PLAYER_M_T_KEY "_player_m_t_key"
#define PLAYER_I_BEEN_TO_ "_player_i_been_to_t"   

#endif
