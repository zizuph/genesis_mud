/*
 * road0.c
 * Kahlen Road
 * by Alaron August 31, 1996
 *
 * Modified by Geraden February 18, 1998 to accomadate for the pass which replaced the
 * elevator.
 * 
 * Modified by Geraden February 18, 1998 to accomadate for the pass which replaced the
 * elevator.
 */



#include "/d/Emerald/carriages/carriage.h"
#include "defs.h"

inherit BASEROAD;
object carriage;

void
create_road()
{
    set_short("Packed dirt road.\nThere is a large sign here");
    set_long("   You are at a crossroads. The hard, dark packed road "+
	     "joins at a four-way intersection. To the north, through "+
	     "low bushes and greenery you can see a large wooden "+
	     "building. Loud sounds of churning water and grinding echo "+
	     "out of the area to the north. The road continues east, west "+
	     "and south down the cliffside onto a string of connected "+
	     "wooden piers. Far to the east a vision of "+
            "a massive, ruined castle fades in and out of the mist.\n"+
             "There is a large sign pounded into the ground on the "+
              "north side of the road.\n\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(IS_CARRIAGE_STOP, 1);
    OUTSIDE;
    LIGHT(1);

    add_item( ({"sign", "large sign"}),
               "This is a large white sign. It has been pounded into the "+
               "ground on the north side of the road. There is some "+
               "writing on it.\n");
    add_item( ({"cliffs", "cliffside"}),
	     "The white and gray cliffs descend to the south along the "+
	     "shore. The cliffs seem to sink underneath the waterline, "+
	     "giving way to a string of connected wooden piers.\n");
	 
    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "low greenery"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"mill", "grist mill", "north", "building", "large building"}),
	     "Off in the distance to the north, you can see a large "+
	     "building through the trees accompanied by loud churning "+
	     "noises. It appears to be a grist mill.\n");

    add_item( ({"wooden piers", "piers", "pier"}),
	     "At the base of the cliffs, as they descend below the "+
	     "waterline to the south, a string of connected wooden "+
	     "piers bobs up and down on the ocean.\n");

    add_item( ({"vision", "massive ruined castle", "castle", "ruined castle"}),
	     "Peering off in the distance to the east, you notice "+
	     "that beyond a thick, wavering mist there is an enormous "+
	     "structure visible. It appears to be a ruined castle of "+
	     "some kind, but you cannot make out very many details from "+
	     "this distance.\n");

    
    add_cmd_item(({"sign", "writing"}), "read",
                 "The sign reads:\n"+
                  "       <----- Kahlen Road ----->\n");
    /* Note the 1 as the last parameter. This is the fatigue
     * factor. This is a supposed default ,but I don't trust them
     * to stay the same. Higher values make it more 'tiring' to walk
     * through the exit.
     */

    add_exit(PATH + "road1", "west", 0, 1);
    add_exit(PATH + "eroad1", "east", 0, 1);
    add_exit(LAKE_DIR + "mill", "north", 0, 1);
    add_exit("/d/Emerald/lake/cleft06", "south", 0, 1);
}

