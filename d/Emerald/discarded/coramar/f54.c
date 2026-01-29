/*
 * F54.c
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
    set_long("   You are standing in the middle of a somewhat wide path, leading "+
	"a meandering course through a mist-shrouded forest. Huge vines drop down "+
	"from shadowy branches high above in the canopy, the soft breeze blowing them "+
	"back and forth across the path. The soft, pleasant sound of water running "+
	"down a fall echos through the air to the northeast. The path continues "+
	"northeast and southwest through the thick layer of fog.\n\n");


    add_fexit(CORAMAR+"f55", "northeast", 0);
    add_fexit(CORAMAR+"f12", "southwest", 0);
    
}
