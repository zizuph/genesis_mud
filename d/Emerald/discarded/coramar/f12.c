/*
 * F12.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   You are standing on a narrow path leading through a mist-shrouded "+
	"forest. The thick blanket of fog hovers over the dark, muddy forest floor, "+
	"distorting and hiding the huge trees behind a screen of murky gray, leaving "+
	"them as nothing more than faint shadows in the background. The foliage on "+
	"either side of the path shoots up out of the ground and reaches high above "+
	"your head. Thick, twisted vines drop down from branches above and dangle "+
	"only a few meters above the forest floor. The path continues to the northeast "+
	"and southwest into the dark gray fog.\n\n");

    add_fexit(CORAMAR+"f54", "northeast", 0);
    add_fexit(CORAMAR+"f12", "southwest", 0);
}