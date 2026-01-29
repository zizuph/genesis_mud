/*
 * F65
 * Forest of Coramar
 * * * * * -- This Room Contains a Way to the Hidden entrance for Mal Askor's caverns 
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You have reached a small clearing in the forest. The dense, blue-gray "+
	"mist seems to be slightly thinner here. A cool breeze seems to be continously "+
	"swirling about the entire area, the bushes and leaves rustling and swaying "+
	"gently in the cold wind. The clearing is edged by huge trees and incredibly "+
	"tall bushes. Thick vines hang down over the clearing from unseen branches "+
	"high above in the forest canopy. The east side of the clearing is dominated "+
	"by the edge of a slope. As your eyes follow the clearing border from west to "+
	"east, you see the greenery fade and eventually give way to the bottom of a "+
	"mountain. The foliage is so thick here that you can only see a few meters of "+
	"width, but it is enough to tell that a mountain must lie somewhere above here. "+
	"Someone has hammered a wooden post here with a sign on it.\n\n");

    add_item( ({"post", "sign", "wooden post", "wood"}),
	"The wooden post has a small sign on it. The sign is a small, brass plate that "+
	"has been pounded carefully into the wood with little wide-headed brass "+
	"tacks. There is writing on the sign.\n");

    add_item("writing",
	"Perhaps you should read it.\n");

    add_cmd_item( ({"writing", "sign"}),
	"read",
	"The writing appears to be in common. The lettering is painstakingly carved "+
	"and flawless. It reads:\n"+
	"    Mal Askor\n\n"+
	"    Seek Ye Treasure In the Center of the Fire?\n"+
	"    Desire Ye Glory in the Belly of the Dragon?\n"+
	"    Need Ye Power more than Thine Own Soul?\n\n"+
	"    Unheeded Warnings can Save No One.\n");

    add_fexit(CORAMAR+"f38", "west", 0);
}