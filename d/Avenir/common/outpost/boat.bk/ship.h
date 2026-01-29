// -*-C++-*-
// $Id: ship.h,v 1.4 1995/09/12 17:27:49 bob Exp $
// ship.h
// creator(s):   Kazz  April 1995
// last update:  Boriska, Sep 1995 Changes through all ship code.
// purpose:      To be #included in all outpost/boat files related to the boat.
// note:         
// bug(s):
// to-do:

#define SEA           "/d/Avenir/common/outpost/boat/"
#define BOAT_DIR      "/d/Avenir/common/outpost/boat/"

#define FORT_DOCK     "/d/Avenir/common/outpost/boat/boat_path2"
#define BAZAAR_DOCK   "/d/Avenir/common/bazaar/pier/float"

// creature defines for the 'state' of the 'captain'
#define FED		1
#define HUNGRY          2

// Time values in seconds.

// wait in port, we're always switch to HUNGRY when arriving to port.
// People will have to feed us again despite all food they could give us
// before. 
#define WAIT_TIME  45

// Time between stops when FED.
#define SAIL_TIME  10

// time betweed feeding the beast at dock and journey start
#define LEAVING_TIME 15

// how many grams to subtract each room/swim
// 	/d/Krynn/solace/village/obj/potatoes  = 350
// 	/d/Krynn/solace/village/obj/apple  = 110
// 	/d/Krynn/solamn/hctower/spur/obj/cake = 130
// 	egg = 50
#define FOOD_CONSUMPTION   75

// waiting times are multiplied by this when we're hungry.
#define HUNGER_FACTOR   2




