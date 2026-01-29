/*
 * F75.c
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
    set_long("   You are standing in a wide path through the mist-shrouded forest. A "+
	"small break in the trees leads down to the bank of a swift-moving mountain "+
	"spring to the west. Huge bushes and trees spring out of the ground on all "+
	"sides of the path, the smallest bush being at least twice your height. Dominating "+
	"the entire trail is a huge, fallen tree. The trunk is twice as wide as you "+
	"are tall. It looks as though it must have fallen from the other side of the "+
	"stream and landed here, right in the middle of the trail. A cold breeze blows "+
	"through the area, making an odd whistling noise as it blows through the holes "+
	"in the rotting tree trunk. The only way to continue east is to walk on the "+
	"tree trunk itself.\n\n");


    add_item( ({"tree", "fallen tree", "log", "fallen log", "trunk",
	"tree trunk"}),
	"The huge tree takes up the entire width of the path, and judging "+
	"from some of the crushed foliage surrounding the path, it takes up "+	
	"more than the width of the path. Its wood is dark and covered with moss "+
	"and an extremely slippery liquid that is a combination of wood rot, moss, "+
	"and moisture from the surrounding air. It makes walking on the massive "+
	"tree trunk a very difficult and slow-moving process.\n");
   

    add_fexit(CORAMAR+"f76", "east", 0);
    add_fexit(CORAMAR+"f60", "west", 0);
}


leave_inv(object ob, object to)
{
    if (interactive(ob))
    {
       if (file_name(to) == "/d/Emerald/coramar/f76")
         ob->catch_msg("You grab hold of a gnarled, slimy branch and haul yourself "+
		"up onto the tree trunk and continue east ...\n\n");
    }
}