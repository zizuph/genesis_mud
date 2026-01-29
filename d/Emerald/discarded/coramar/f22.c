/*
 * F22
 * Coramar Forest
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_room()
{
    set_long("   You have found yourself at a junction of several paths "+
	"through the mist-shrouded forest. The paths here are narrow "+
	"and surrounded on all sides by sprawling, overgrown foliage and "+
	"trees. Vines hang down to a point just above the forest floor "+
	"from giant branches hidden by the dense fog above. One of the "+
	"branches of the path leads west into a more narrow path concealed "+
	"behind the veil of gray moisture. Another branch leads northeast "+
	"onto a trail which appears to widen just before the swirling "+
	"mists move in and conceal your view of it. The third path "+
	"is a narrow path that leads southeast into the dark mist toward "+
	"the sound of running water.\n\n");


    add_fexit(CORAMAR+"f23", "northeast", 0);
    add_fexit(CORAMAR+"f59", "southeast", 0);
    add_fexit(CORAMAR+"f21", "west", 0);
}