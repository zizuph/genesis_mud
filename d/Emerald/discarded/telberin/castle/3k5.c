/*
 * 3k5.c
 * Library in Castle Telberin
 * Book in here contains ritual to join the Keepers of Telberin
 * - Alaron February 1997
 */


#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();

    set_short("Small Study");
    set_long("   The small room has the look of a study. It is lined with "+
	     "stone-carved bookshelves on every wall, almost completely "+
	     "masking the eerily glowing green stone beyond. The stone "+
	     "floor is tiled and the chips, cracks and stains betray its "+
	     "age to be far older than the rooms surrounding it. There is "+
	     "a table in the middle of the room with a single book resting "+
	     "on it. A single door leads south out of the study.\n\n");

    add_item(({"shelves", "bookshelves", "books", "shelf",
	       "stone-carved bookshelves", "bookshelf", "stone shelves"}),
	     "The stone-carved bookshelves are large and made of a thick, "+
	     "sturdy gray stone. It has been smoothed, polished and "+
	     "layered with some kind of glaze which gives the stone a "+
	     "marble-like reflective property. The books contained in the "+
	     "shelves look extremely old and valuable.\n");

    remove_item("floor");

    add_item(({"floor", "stone floor", "tiles", "tiled floor", "chips",
	       "cracks", "stains", "down", "ground"}),
	     "The dark, gray stone floor stands out in stark contrast "+
	     "with the subtly glowing emerald-green walls. The age of "+
	     "the floor is apparent in the cracks, stains and marks left "+
	     "by ages of collecting dust and moisture.\n");

    add_item("table",
	     "There is a table in the center of the room. A strange, greenish "+
	     "light seems to illuminate the table, yet you can't determine "+
	     "the source. Examining the table further, you notice that it "+
	     "is made of ancient wood, glazed and lacquered over and over "+
	     "again to preserve the aging wood beneath. Despite all efforts, "+
	     "the age of the table is beginning to appear yet again. A large, "+
	     "leather-bound book rests in the middle of the table, open "+
	     "to a page somewhere in the first quarter of the book.\n");

    add_item( ({"book", "leather book", "large book", "leather-bound book",
		"large leather-bound book"}),
	     "The large, leather-bound book looks to be quite old. The pages "+
	     "of the book have long since become brittle and yellowed. It "+
	     "looks like you could probably crumble the book to dust if "+
	     "you tried to change the page that it is open to. You wonder "+
	     "why someone would have left the book open to a particular "+
	     "page rather than preserving it.\n");

    add_cmd_item("page", "read",
		 "Taking care not to touch the book, you begin reading "+
		 "the page:\n\n"+
		 "Ritual of Joining the Keepers of Telberin\n"+
		 "\n"+
		 "First of all, none may join the Keepers of Telberin "+
		 "without the blessing of the Initiator. This elf is "+
		 "typically one who has earned the undying respect of "+
		 "his or her peers, as well as attained the rank of "+
		 "Lord Commander of the Protectorate of Telberin. The "+
		 "Initiator traditionally bestows a small gift upon "+
		 "the Initiate. This gift is a physical symbol of the "+
		 "Initiator's blessing.\n"+
		 "\n"+
		 "The ritual itself is solemn and quick, without much "+
		 "ceremony. Most elves know that they are destined for "+
		 "becoming a Keeper since their childhood, and so there "+
		 "is little cause for ceremony when the joining is actually "+
		 "done.\n"+
		 "Those who show their gift to the King of Telberin will "+
		 "be granted entrance into the Protectorate, as his "+
		 "ancestor once was.\n"+
		 "Those who show their gift to the Queen of Telberin will "+
		 "be granted entrance into the Order, as her ancestor "+
		 "once was.\n"+
		 "The ritual is then complete, at which point most people "+
		 "agree that it is time to celebrate, and continue doing "+
		 "so for quite a long period of time.\n\n");

   add_exit(CASTLE_DIR + "3k2","south");
}

