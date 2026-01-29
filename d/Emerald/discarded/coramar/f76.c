/*
 * F76.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("Atop a giant, fallen tree");

    set_long("   You are standing atop a giant, fallen tree trunk. It looks as "+
	"though it fell from further to the west and landed here, in the middle of "+
	"what used to be a trail through the mist-shrouded forest. The thick bank of "+
	"mist hovers right at the top of the tree trunk, making visibility here "+
	"incredibly poor. A cold wind gusts through the area, rustling the leaves "+
	"of nearby trees and causing the vines to sway quickly back and forth. The "+
	"breeze makes an eerie howling noise as it blows through the rotted holes and "+
	"knots in the tree trunk. The only way to continue in either direction is to "+
	"try and maintain your balance on the top of the moss-covered trunk.\n\n");

    add_item( ({"tree", "fallen tree", "log", "fallen log", "trunk",
	"tree trunk"}),
	"The huge tree takes up the entire width of the path, and judging "+
	"from some of the crushed foliage surrounding the path, it takes up "+	
	"more than the width of the path. Its wood is dark and covered with moss "+
	"and an extremely slippery liquid that is a combination of wood rot, moss, "+
	"and moisture from the surrounding air. It makes walking on the massive "+
	"tree trunk a very difficult and slow-moving process.\n");
   

    add_fexit(CORAMAR+"f67", "east", 0);
    add_fexit(CORAMAR+"f75", "west", 0);
}


leave_inv(object ob, object to)
{
    if (interactive(ob))
    {
	ob->catch_msg("You slip and slide on the slick surface of the moist, rotting "+
		"wood but still manage to maneuver without falling ... \n\n");
    }
}