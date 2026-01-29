/*
 * COAST5.c
 * This is the coastal road / path leading to the monk ruins.
 * Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
  set_short("Dark, foggy path");
  set_long("   The dark, gray area is cold and damp. The fog looms heavily "+
	   "over the path, distorting its features and concealing its "+
	   "destination. Off in the distance to the southeast you can see "+
	   "the huge, ominous dark shadows of buildings hidden behind "+
	   "the veil of mist. The grass and bushes on the path have been "+
	   "trampled by frequent use, although some of the old trenches "+
	   "worn by wagon traffic are beginning to fade. The path continues "+
	   "further into the enclosing mist to the east and to the "+
	   "northwest. Just a bit to the north and east, you can sense "+
	   "more than actually see where the bushes drop off as they meet "+
	   "the ocean cliffs.\n\n");

  add_item( ({"fog", "dark fog", "dark gray fog", "mist", "veil", "veil of mist",
	      "cloud", "cloud of mist"}),
	   "The dark gray mist looms over the entire area, seemingly stifling all "+
	   "of the sounds near the path. The hushed silence is eerie and "+
	   "unsettling. The fog additionally soaks the ground, grass and weeds "+
	   "with a thick, cold dew.\n");
  
  add_item( ({"dew", "thick dew", "cold dew"}),
	   "The thick, cold dew rests on the grass, the weeds and the path "+
	   "beneath you, coating your clothing with moisture as you step "+
	   "through the fog.\n");
  
  add_item( ({"shadows", "buildings", "huge shadows", "huge buildings"}),
	   "The dark shadows looming in the distance to the southeast "+
	   "are nothing more than vague outlines beyond the point of "+
	   "clear visibility through the veil of mist. You can guess that "+
	   "the shadows are the outlines of buildings of some kind, but you "+
	   "can't quite be sure from this vantage point.\n");
  
  add_item( ({"grass", "bushes", "ground", "path", "down"}),
	   "The grass and bushes that have been trampled and flattened as a result "+
	   "of frequent use of this area of clearing which closely resembles a path "+
	   "are soaking wet with moisture condensed out of the perpetually "+
	   "hanging cloud of mist.\n");
  
  add_exit(MONKRUIN_DIR + "coast6", "east");
  add_exit(MONKRUIN_DIR + "coast4", "northwest");
}

















