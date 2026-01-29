/* This file contains the descriptions of all the rooms for the
 * area_handler. Macros allow easy combination of different
 * descriptions :)
 */

#define PL1_S     "On the plains of Abanasinia"
#define PL1_L     "You are standing in the middle of nowhere. The landscape " +\
                  "is undulating a little, and there is grass and " +\
		  "several bushes and even small trees, disallowing " +\
		  "you to look very far."
#define PL2_L     "You are standing on a vast plain. There are a few bushes " +\
                  "and trees about, and the ground is covered with brownish " +\
		  "grass everywhere."

#define R1_S      "On the Sageway"
#define R1_L      "You find yourself on the Sageway crossing the plains of Abanasinia. " +\
                  "The track has been cleared of vegetation and you can easily walk along."
#define R2_L      "This is the Sageway over the plains of Abanasinia. The road you " +\
                  "walk on is clearly visible in between the bushes and grass."
#define R3_L      "The track you stand on is commonly known as the Sageway. It leads " +\
                  "across the plains of Abanasinia."
#define VEGETATION ({"vegetation"}),"You don't find any on the road. The vegetation aside " + \
                   "the road around here consists mostly of grass. " +\
                   "Bushes and trees are scattered about, too, just enough to reduce " +\
                   "visibility drastically.\n"
#define BUSH_TREE  ({"bush","bushes","tree","trees"}), \
		   "These are ordinary bushes and trees. " +\
		   "Some of them even have a few green leaves still, though " +\
		   "most is uniformly brown.\n"
#define GRASS      "grass","It is brownish grass growing on the ground everywhere.\n"
#define HILLS      "hills","They are not very high and covered with grass, trees and bushes.\n"

#define ON_A_ROAD ({ ({ ROOM_NORMAL, 0, 1 }),\
                     ({ R1_S, R1_L, R2_L, R3_L }),\
                     ({ VEGETATION, BUSH_TREE, GRASS }),\
                     ({ }) })
#define IN_A_VALLEY ({ ({ ROOM_NORMAL, 0, 3 }),\
                     ({ "In a valley",\
			"Hills are on both sides of you, enclosing the cozy valley " +\
			"you are in. A few bushes and trees are around and it is easily " +\
			"possible to continue along the valley.",\
			"You are in a small valley enclosed by hills on two sides. " +\
			"It is easily possible to walk along the valley." }),\
                     ({ VEGETATION, BUSH_TREE, GRASS, HILLS }),\
                     ({ }) })
