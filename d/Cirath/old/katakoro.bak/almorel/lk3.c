/*
	Asmodean, March 18, 1995
	LK3 - Property of the Cirath Domain
*/

#include "almorel.h"
#include "Lakes.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
    set_short("Lakeside street");
    set_long("The Mist street comes to a dead end at a circle of "+
	"small houses. In the center of the circle is a larger "+
	"house with a fence surrounding it. There is a stable and "+
	"a workhouse attached directly to the main house. Only the "+
	"most wealthy and powerful people in Almorel can afford to "+
	"live in such luxury. The circle of houses surrounding the "+
	"villa most likely belong to the servants and employees "+
	"of the wealthy family. Beyond the house the outer village "+
	"wall can be seen, everpresent in its defense of the people "+
	"of Almorel.\n\n");

    add_exit(ALMOREL+"lk2","southwest");

    add_item("wall",
	"The wall is a marvel of construction. Using enormous felled "+
	"trees stacked one on top of the other, the people of Almorel "+
	"have created a defensive, almost Cyclopean in size, wall. It "+
	"stands a good fifty feet high. The trees have been mortared "+
	"together with clay, mud and other adhesive materials, with "+
	"thick iron bars periodically placed along the wall for "+
	"support in strong weather.\n");
}

