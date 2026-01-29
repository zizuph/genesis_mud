/*********************************************************************
 * - fruit.h                                                       - *
 * - Contains common defines for fruit picking.                    - *
 * - Created by Damaris@Genesis 03/2006                            - *
 *********************************************************************/

#ifndef __FRUIT_DEFS__
#define __FRUIT_DEFS__

#include <macros.h>

/* Path to the clonable fruit object */
#define FRUIT_PATH	"/d/Khalakhor/guilds/tempt/room/fruit"

/*********************************************************************
 * - An Array containing pick limit per player, and limit per boot - *
 * - for all. The boot limit is for all rooms, so we set it kinda  - *
 * - high. The 2 elements are the limit strings.. player/boot.     - *
 *********************************************************************/
 
#define FRUIT_LIMIT ({ 5, 700, "You have picked enough fruits, leave "+ \
	"some for others.\n", "Sorry, the area has been picked "+ \
	"clean of fruits, wait for them to grow back.\n" })

/* Mapping containg fruits and their food values (for when eating) */
#define FRUITS ([ \
	"cherry"      :  20, \
   	"grape"       :  20, \
	"blackberry"  :  20, \
	"blueberry"   :  20, \
	"raspberry"   :  20, \
	"gooseberry"  :  20, \
	"strawberry"  :  20, \
	"plum"        :  40, \
	"pomegranate" :  40, \
	"orange"      :  40, \
	"lemon"       :  40, \
	"peach"       :  40, \
	"melon"       : 100, \
		])

/* Mapping containe special long descs for fruits. */
#define FRUIT_LONG ([ \
       "cherry"     : "A handful of very red, long-stemmed cherries "+ \
                      "that have been picked at the peak of ripeness.\n", \
       "grape"      : "A handful of succulent red and white grapes "+ \
	              "that have been picked at the peak of ripeness.\n", \
       "blackberry" : "A handful of very dark, blackberries that have "+ \
	              "been picked at the peak of ripeness.\n", \
       "blueberry"  : "A handful of sweet, plump blueberries that have "+ \
	              "been picked at the peak of ripeness.\n", \
       "raspberry"  : "A handful of very red, plump raspberries that "+ \
	              "have been picked at the peak of ripeness.\n", \
       "gooseberry" : "A handful of sweet, plump gooseberries that "+ \
	              "have been picked at the peak of ripeness.\n", \
       "strawberry" : "A handful of very red, plump strawberries that "+ \
	              "have been picked at the peak of ripeness.\n", \
		])

/* Mapping containing an array of special short & pshort descs. */
#define FRUIT_SHORT ([ \
	"cherry" : ({ "handful of cherries", "handfuls of cherries"}), \
	"grape" : ({ "handful of grapes", "handfuls of grapes"}), \
	"blackberry" : ({ "handful of blackberries", "handfuls of blackberries"}), \
	"blueberry" : ({ "handful of blueberries", "handfuls of blueberries"}), \
	"raspberry" : ({ "handful of raspberries", "handfuls of raspberries"}), \
	"gooseberry" : ({ "handful of gooseberries", "handfuls of gooseberries"}), \
	"strawberry" : ({ "handful of strawberries", "handfuls of strawberries"}), \
			])

/* Mapping containing specific adjectives to set, please limit to 2. */
#define FRUIT_ADJS ([ \
	"cherry" : ({"long-stemmed"}), \
		])
/*********************************************************************
 * - Mapping containg pointes to fruit 'special_effct' messages to - *
 * - be printed when eaten.  If the value is a string, eater will  - *
 * - have the string printed to them.  Same if a single element    - *
 * - string array.  If a two element string array, the second      - *
 *********************************************************************/
#define FRUIT_SPC ([ \
	"orange" : ({ "You quickly peel the orange.", \
		QCTNAME(this_player()) + " quickly peels "+ \
		"an orange." }), \
		])

#endif  __FRUIT_DEFS__
