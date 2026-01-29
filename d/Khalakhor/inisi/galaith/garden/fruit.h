/*
 * - fruit.h
 *
 * Contains common defines for fruit picking.
 */

#ifndef __FRUIT_DEFS__
#define __FRUIT_DEFS__

#include <macros.h>

/*
 * Path to the clonable fruit object
 */
#define FRUIT_PATH	"/d/Khalakhor/inisi/galaith/garden/fruit"

/*
 * Array containing pick limit per player, and limit per boot for all.
 * The boot limit is for all rooms, so we set it kinda high.
 * Not terribly realistic, but hey, it's much easier this way.
 * The 2 elements are the limit strings.. player/boot
 */
#define FRUIT_LIMIT ({ 3, 300, "You have picked enough fruits, leave "+ \
	"some for others.\n", "Sorry, they garden has been picked "+ \
	"clean of ripe fruits, you will have to return another day.\n" })

/*
 * Mapping containg fruits and their food values (for when eating)
 */
#define FRUITS ([ \
	"cherry" :  10, \
	"blackberry" :  10, \
	"blueberry" :  10, \
	"raspberry" : 10, \
	"gooseberry" : 10, \
	"strawberry" : 10, \
	"plum" : 20, \
	"pomegranate" :  20, \
	"orange" :  20, \
	"lemon" :  20, \
	"peach" :  20, \
	"melon" : 100, \
		])

/*
 * Mapping containe special long descs for fruits.
 */
#define FRUIT_LONG ([ \
	"cherry" : "A handful of very red, long-stemmed cherries.\n", \
	"blackberry" : "A handful of very dark, blackberries.\n", \
	"blueberry" : "A handful of sweet, plump blueberries.\n", \
	"raspberry" : "A handful of very red, plump raspberries.\n", \
	"gooseberry" : "A handful of sweet, plump gooseberries.\n", \
	"strawberry" : "A handful of very red, plump strawberries.\n", \
		])

/*
 * Mapping containing an array of special short & pshort descs.
 */
#define FRUIT_SHORT ([ \
	"cherry" : ({ "handful of cherries", "handfuls of cherries"}), \
	"blackberry" : ({ "handful of blackberries", "handfuls of blackberries"}), \
	"blueberry" : ({ "handful of blueberries", "handfuls of blueberries"}), \
	"raspberry" : ({ "handful of raspberries", "handfuls of raspberries"}), \
	"gooseberry" : ({ "handful of gooseberries", "handfuls of gooseberries"}), \
	"strawberry" : ({ "handful of strawberries", "handfuls of strawberries"}), \
			])

/*
 * Mapping containing specific adjectives to set, please limit to 2.
 */
#define FRUIT_ADJS ([ \
	"cherry" : ({"long-stemmed"}), \
		])
/*
 * Mapping containg pointes to fruit 'special_effct' messages
 * to be printed when eaten.  If the value is a string, eater will
 * have the string printed to them.  Same if a single element
 * string array.  If a two element string array, the second element
 * will be printed to onlookers.
 */
#define FRUIT_SPC ([ \
	"orange" : ({ "You quickly peel the orange.", \
		QCTNAME(this_player()) + " quickly peels "+ \
		"an orange." }), \
		])

#endif  __FRUIT_DEFS__
