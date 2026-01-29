
/*
 * KOT_HQ2.c
 * Keepers of Telberin Guild Hall - Cleric's Training Room
 * - Alaron January 1997
 */

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/room";
inherit "/lib/skill_raise";

void
create_room()
{
    set_short("Chamber of Knowledge");
    set_long("   The room has a musty, damp feel to it. The lighting in "+
	     "here is poorly centered, leaving a dark shadow in the "+
	     "middle of the room while sufficiently illuminating three "+
	     "tables in the corners of the room. Massive bookshelves "+
	     "completely hide the walls from view, displaying a vast "+
	     "array of books, scrolls, and tomes from floor to "+
	     "ceiling. Most of the books on the shelves lay gathering "+
	     "dust and cobwebs, while others appear well read and "+
	     "frequently used. Stacks upon stacks of books rest against "+
	     "the few remaining open wall spaces, as well as in front of "+
	     "bookshelves too full to hold any more volumes. Narrow "+
	    "doorways lead out of the room to the northwest and southwest.\n\n");
  
    add_prop(ROOM_I_INSIDE, 1);
  
    add_item( ({"tables", "corners"}),
	      "Three tables occupy three of the corners in the room. The "+
	      "tables are nearly chest-high to an average elf, and do not "+
	      "have a stool or table in front of them. It looks like they "+
	      "are designed to allow the reader to peruse texts while "+
	      "standing. At the head of each of the tables is a large, "+
	      "oil-filled lamp providing plenty of reading light.\n");
  
    add_item(({"lamp", "large lamp", "oil lamp", "oil-filled lamp",
		 "large oil-filled lamp", "lamps', 'oil lamps"}),
	     "The oil lamps are large and appear to be nearly full "+
	     "of fuel. Their unsteady glow casts shadows about the room "+
	     "which converge in the center. The lamps on the tables "+
	     "create three points of light in the room, while the center "+
	     "remains in utter darkness.\n");
  
    add_item( ({"bookshelves", "massive bookshelves"}),
	      "Massive bookshelves almost completely hide the walls of "+
	      "the room behind their contents. Each shelf is filled to "+
	      "overflowing. So much so that some volumes have been "+
	      "stacked on their sides atop the books already on the "+
	      "shelves.\n");
  
    add_item( ({"books", "scrolls", "texts", "volumes", "tomes"}),
	      "The room is absolutely inundated with books and "+
	      "texts. Many of the books on the shelves appear ancient "+
	      "and are covered with dust and cobwebs. However, other "+
	      "books are dust-free and appear to be used quite "+
	      "often. Stacks of books rest in front of the bookshelves "+
	      "due to lack of shelfspace.\n");
  
    add_item( ({"stacks", "piles", "book stacks", "stacks of books"}),
	      "Dozens of stacks of books rest on the floor in front "+
	      "of the shelves due to lack of available shelf space. It "+
	      "is obvious that there are far more books here than this "+
	      "relatively small room can support.\n");
  
    add_item( ({"doorway", "doorways", "narrow doorways", "doors"}),
	    "The narrow doorways do not have doors in them, and as "+
	    "such are more like mere openings than doorways. They lead "+
	    "out of this chamber to the northwest and southwest.\n");

    create_skill_raise();
    sk_add_train(SS_SPELLCRAFT, "understand magic theory", 0, 0, 35);
    sk_add_train(SS_HERBALISM, "forage for and identify herbs", 0, 0, 40);
    sk_add_train(SS_LOC_SENSE, 
        "determine your location and direction", 0, 0, 50);
    sk_add_train(SS_LANGUAGE, "speak foreign and archaic languages", 0, 0, 50);
    sk_add_train(SS_ELEMENT_LIFE, "use life magic", 0, 0, 30);
    sk_add_train(SS_FORM_CONJURATION, "conjure", 0, 0, 10);

    add_exit("kot_hq1", "southwest");
    add_exit("kot_common", "northwest");
}

void
init()
{
    init_skill_raise();
    ::init();
}
