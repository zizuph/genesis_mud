/*
 * Filename: /d/Avenir/common/ships/bazaar/ship.h
 * Original creator: Kazz on Apr 1995
 * Purpose: To be #included in all outpost/boat files related to the boat.
 * Last update(s):
 *    Boriska on Sep 1995 - Changes through all ship code.
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 * Note: add_items are not needed since they can't be examined from the deck
 * Known bug(s):
 * To-do:
 */
#define SEA           "/d/Avenir/common/ships/bazaar/"
#define BOAT_DIR      "/d/Avenir/common/ships/bazaar/"

#define FORT_DOCK     "/d/Avenir/common/ships/bazaar/boat_path2"
#define BAZAAR_DOCK   "/d/Avenir/common/bazaar/pier/float"

/* creature defines for the 'state' of the 'captain' */
#define FED		1
#define HUNGRY          2

/* Note: Time values in seconds. */

/* wait in port, we're always switch to HUNGRY when arriving to port.
 * People will have to feed us again despite all food they could give us
 * before.
 */
#define WAIT_TIME  45

/* Time between stops when FED. */
#define SAIL_TIME  3

/* time betweed feeding the beast at dock and journey start */
#define LEAVING_TIME 15

/* how many grams to subtract each room/swim
 * 	/d/Krynn/solace/village/obj/potatoes  = 350
 * 	/d/Krynn/solace/village/obj/apple  = 110
 * 	/d/Krynn/solamn/hctower/spur/obj/cake = 130
 * 	egg = 50
 */
#define FOOD_CONSUMPTION   75

/* waiting times are multiplied by this when we're hungry. */
#define HUNGER_FACTOR   5
