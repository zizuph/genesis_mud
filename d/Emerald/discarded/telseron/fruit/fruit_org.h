/*
 * FRUIT.h
 * Header file containing fruit definitions
 */

#define STDFRUIT "/std/food"

#define FRUIT_APPLE      0
#define FRUIT_CHERRIES   1
#define FRUIT_WATERMELON 2
#define FRUIT_PEACH      3


#define FRUIT_NAMES ({ "apple", "cherries", "watermelon", "peach" })
#define FRUIT_ADJ ({ ({ "red", "juicy" }), \
		     ({ "red", "juicy" }), \
		     ({ "large", "ripe"}), \
                     ({ "fuzzy", "juicy"}) })

#define FRUIT_LONGS ({ "It is a large, mouthwatering red apple.",\
		       "They're a bunch of deep, juicy cherries.",\
		       "It is a large, juicy watermelon. It will satisfy "+\
                         "almost anyone's appetite.",\
                       "It is a large, juicy peach. Your mouth waters "+\
                         "in anticipation." })

#define FRUIT_AMOUNTS ({ 50, 50, 50, 50 })

#define FRUIT_WEIGHTS ({ 100, 100, 500, 100 })
#define FRUIT_VOLUMES ({  60,  60, 250,  60 })
