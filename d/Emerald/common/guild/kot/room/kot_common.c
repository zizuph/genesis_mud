/*
 * KOT_COMMON.c
 * Keepers of Telberin Common Room
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "../guild.h"

inherit "/std/room";

void
create_room()
{
  set_short("Common Room");
  set_long("   The wide, mahogany-walled room is warm and comforting. "+
	   "Its walls are decorated with pictures of scenes and people "+
	   "of import in the history of Telberin and the Keepers. The "+
	   "floor is made of a cross-hatched pattern of inter-locking "+
	   "wood panels. In the middle of the floor there is a large, "+
	   "fluffy woven rug of mixed earth tones. Between the two "+
	   "doorways leading southwest and southeast is a table "+
	   "with a book of notes on it. Next to the book of notes "+
	   "is an ink and quill set, implying that anyone is free "+
	   "to add to the book. Several large candles provide a "+
	   "dancing amber glow throughout the room from their "+
           "golden holders in the walls. You sense that it is possible "+
            "to <start here>.\n\n");

  add_prop(ROOM_I_INSIDE, 1);

  add_item( ({"walls", "wood walls", "mahogany walls", "mahogany"}),
	    "The mahogany walls are finely polished and smoothed, "+
	    "reflecting the flickering glow of the candles "+
	    "in the room.\n");

  add_item( ({"floor", "down", "ground", "pattern", "panels",
		"wood panels"}),
	    "The floor is made of wooden panels interlocking "+
	    "in an simple, but impressive pattern. In the middle "+
	    "of the floor is a large, fluffy woven rug of "+
	    "earth tones.\n");

  add_item( ({"rug", "fluffy rug", "woven rug", "fluffy woven rug",
		"large rug" ,"large fluffy rug"}),
	    "The large rug on the floor in the middle of the room "+
	    "is made of a fluffy, woven material. The material has "+
	    "multiple colors of earth tones.\n");

  add_item("table",
	   "There is a table resting between the two doorways leading "+
	   "out of this room. Upon the table is a book of notes and "+
	   "an ink and quill set.\n");

  add_item( ({"set", "ink set", "quill set", "ink and quill set",
		"ink", "quill"}),
	    "The ink and quill set next to the book of notes is "+
	    "simple and plain, but useful. It gives you the impression "+
	    "that writing in the book of notes is encouraged.\n");

  // note that the item for the book is not needed, since the book
  // will be an object

    reset_euid();
    clone_object(KOT_OBJ_DIR + "board")->move(this_object(), 1);
/*
    clone_object("/d/Emerald/common/guild/kot/log/vote")->move(this_object(), 1);
*/

    add_cmd_item("here", "start", "@@do_starter@@");

    add_exit("kot_hq3", "southwest", "@@no_Order@@");
    add_exit("kot_hq2", "southeast", "@@no_Prot@@");
    add_exit("library", "north");
}

int
no_Order()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

   if (this_player()->query_kot_caste() != WARRIOR_CASTE)
    {
        write("You sense that you should not be entering the "+
              "training room of the Protectorate.\n");
         return 1;
     }
}

int 
no_Prot()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    if (this_player()->query_kot_caste() != CLERIC_CASTE)
     {
        write("You sense that you should not be entering the "+
               "training room of the Order.\n");
         return 1;
      }
}

int
do_starter()
{
    this_player()->set_default_start_location(file_name(this_object()));
    write("You feel as though you have a new home, now.\n");
    return 1;
}
