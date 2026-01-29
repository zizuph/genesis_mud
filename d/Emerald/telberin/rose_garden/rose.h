/*
 * - rose.h
 *
 * Contains common defines for rose picking.
 */

#ifndef __ROSE_DEFS__
#define __ROSE_DEFS__

/*
 * Path to the clonable rose object
 */
#define ROSE_PATH	"/d/Emerald/telberin/rose_garden/rose"

/*
 * Array containing pick limit per player, and limit per boot for all.
 * The boot limit is for all rooms, so we set it kinda high.
 * Not terribly realistic, but hey, it's much easier this way.
 * The 2 elements are the limit strings.. player/boot
 */
#define ROSE_LIMIT ({ 3, 300, "You have picked enough roses, leave "+ \
	"some for others.\n", "Sorry, the garden can't be picked at "+ \
	"this time.\n" })

/*
 * Mapping containing roses and their stem types.
 */
#define ROSES ([ \
	       "orange" : "long-stemmed", \
	          "red" : "short-stemmed", \
	     "dark red" : "long-stemmed", \
	       "yellow" : "long-stemmed", \
	"bright yellow" : "short-stemmed", \
	         "pink" : "long-stemmed", \
	    "pale pink" : "short-stemmed", \
		])

/*
 * Mapping contain special long descs for roses.
 */
#define ROSE_LONG ([ \
	 "orange" : "A long-stemmed Angels Mateu rose. It has double, "+ \
		    "globular petals in a bright orange-rose color. "+ \
		    "It is big, bright, and eye-catching flower.\n", \
	    "red" : "A short-stemmed Crimson Glory rose. It is a "+ \
		    "gorgeous flower with very dark red velvety petals, "+ \
		    "that are soft to the touch.\n", \
       "dark red" : "A long-stemmed Crimson Glory rose. It is a "+ \
		    "gorgeous flower with very dark red velvety petals, "+ \
		    "that are soft to the touch.\n", \
         "yellow" : "A beautiful long-stemmed yellow rose.\n", \
  "bright yellow" : "A beautiful short-stemmed yellow rose.\n", \
	   "pink" : "A long-stemmed Briarcliff rose. It is a big rose "+ \
		    "with double petals in a bright rose-pink color.\n", \
      "pale pink" : "A short-stemmed Briarcliff rose. It is a big rose "+ \
		    "with double petals in a pale rose-pink color.\n", \
		])
/*
 * Mapping containing an array of special short & pshort descs.
 */
#define ROSE_SHORT ([ ])

#endif  __ROSE_DEFS__
