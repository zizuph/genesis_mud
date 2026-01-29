/*
 * STAIRS.c
 * Stairs leading up to the Keepers of Telberin Guild Area
 * Original by Jasmine
 * Re-desc by Alaron August 15, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
  set_short("stairs");
  set_long("    You stand upon a high-reaching, marble staircase. Its "+
	   "majestic steps climb upward toward an enormous red oak door "+
	   "set into the stone of the castle wall. As you walk along the "+
	   "steps, making a soft, muffled click with each footfall against "+
	   "the smooth stone, you look around at the magnificent tapestries. "+
	   "Bright, detailed, multi-colored tapestries hang from the cold "+
	   "gray stone walls, adding a feeling of warmth and security to "+
	   "the otherwise barren stairwell. Beneath each of the "+
	   "tapestries are extremely well-designed oak shelves whose "+
	   "bases follow the pattern of the rising stairs exactly. "+
	   "Looking up at the door, you feel safe and warm here.\n\n");

  add_item( ({"shelf", "shelves", "oak shelves", "well-designed shelves"}),
	   "These shelves are amazing. Their bases are made to taper "+
	   "upward at a stepped incline exactly matching the stairwell, so "+
	   "each of the shelf bottoms remains level and flat. They are "+
	   "line with trophies, banners, awards and symbols of victories.\n");

  add_item(({"bright tapestries", "detailed tapestries",
	     "multi-colored tapestries",
	     "tapestries" }),
	   "The magnificent tapestries hang from the high ceiling in "+
	   "colorful, comforting splendor. They depict pictures of the "+
	   "past displaying victories won and proud accomplishments. There "+
	   "is even a section of one of the tapestries which displays a "+
	   "schematic-like map of a city.\n");

  add_item( ({"map", "schematic map", "city"}),
	   "The map is a schematic-like diagram of what appears to be "+
	   "an ancient city. Written in perfect calligraphy above the "+
           "map is the word \"Kortathor\"\n");

  add_item( ({"door", "large door", "oak door", "red oak door"}),
	   "The enormous door at the head of the stairs seems to "+
	   "stand atop the climb like a guardian, keeping out "+
	   "unwanted visitors.\n");


  add_exit(CASTLE_DIR + "th7", "down");
  add_exit(CASTLE_DIR + "3k1", "up", "@@go_stairs@@");

  add_item(({"stairs","stair"}),"The stairs lead up to the oak door.\n");

}

/*
 * GO_STAIRS
 * currently prints a nifty message, add a check for who can go
 * upstairs if you like, this is a good place to implement it.
 */

int
go_stairs()
{
    write("\nYou ascend the rest of the stairs and gently push through "+
	  "the heavy oak door, its hinges creaking softly against the "+
          "weight ...\n\n");
    say(QCTNAME(this_player())+" ascends the rest of the stairs and "+
	"gently pushes through the heavy oak door, its hinges creaking "+
	"softly against the weight.\n");
    

    /* returns 0 now, return 1 and print message if can't go up */
    return 0;
}

