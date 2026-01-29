/*
 * F67.c
 * Another section of the coramar forest. 
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
	"by the thick blanket of gray fog. The trail here runs north alongside the "+
	"towering wall of green, and also continues to the west into the bleak "+
	"grayness. A cool, wet breeze blows up and down the trail, rustling the bushes "+
	"and causing the hanging vines to sway back and forth.\n\n");

    add_item( ({"wall", "wall of vegatation", "wall of green", "shades", "green",
	"foliage", "wall of foliage"}),
	"It is a huge wall of tangled vegetation, greenery, plants, grass, vines and "+
	"hundreds of crawling plants. It seems to spread up into the gray mist "+
	"forever until it is no longer discernable.\n");

  
    add_exit(CORAMAR+"f66", "north", 0);
    add_exit(CORAMAR+"f42", "south", 0);
}