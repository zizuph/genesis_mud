/*
 * F34.c
 * Another section of the coramar forest. Contains hidden exit into a 
 * non-obvious section of the forest. That section contains the entrance
 * to the hidden section of the forest containing Mal Askor and another runestone.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are standing alongside what looks to be a titanic wall of "+
	"green foliage. Plants of all shapes and sizes, leaves and vines all form "+
	"an enormous tangle containing thousands of shades of green. The wall of "+
	"vegetation is so high that the very top of it is completely hidden above "+
	"by the thick blanket of gray fog. The trail here runs south alongside the "+
	"towering wall of green, and also continues to the northwest into the bleak "+
	"grayness. A cool, wet breeze blows across the trail from the west, and seems "+
	"to blow through the wall of vegetation to the east, making an eerie howling "+
	"noise. The vines sway back and forth in the strong, cold wind.\n\n");

    add_item( ({"wall", "wall of vegatation", "wall of green", "shades", "green",
	"foliage", "wall of foliage"}),
	"It is a huge wall of tangled vegetation, greenery, plants, grass, vines and "+
	"hundreds of crawling plants. It seems to spread up into the gray mist "+
	"forever until it is no longer discernable. You wonder what could have caused "+
	"this formation to appear on the side of the path.\n");

  
    add_exit(CORAMAR+"f33", "northwest", 0);
    add_exit(CORAMAR+"f35", "east", 1);
    add_exit(CORAMAR+"f66", "south", 0);
}