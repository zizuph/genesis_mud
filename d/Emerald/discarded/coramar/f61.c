/*
 * f61
 * Coramar Forest
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    quiet();


    set_short("A stream through the forest");

    set_long("   You are standing knee-deep in the icy waters of a "+
	"mountain spring. Its current is so strong that it takes constant "+
	"effort to avoid being swept downstream among the smooth rocks and "+
	"forest debris. Thick, twisted vines drop down into the water "+
	"from branches so low that you have to duck to avoid them. The "+
	"narrow stream, low branches and tangles of vines give the impression "+
	"of a cave. The thick blanket of mist hovering over the water "+
	"further adds to the confined, cave-like feeling of the mountain "+
	"spring. It continues downstream to the southeast.\n\n");

    add_item( ({"water", "stream", "brook" , "river", "runoff", "spring"}),
	"The water from the mountain spring is as cold as ice. The "+
	"water is clear and looks as though it would taste "+
	"wonderfully refreshing on a hot day. The surface of the water "+
	"is cluttered by fallen leaves and the hanging vines. It descends "+
	"from the northwest and continues southeast to "+
	"lower elevations.\n");

    add_item( ({"rocks", "smooth rocks"}),
	"The smooth rocks of the river look as though they may have once "+
	"been large rocks that tumbled into the river from the mountains "+
	"above and have become nothing more than colorful, smooth "+
	"pebbles over the centuries of erosion.\n");

    remove_item("vines");
    add_item( ({"vines", "thick vines", "twisting vines",
	"thick twisting vines"}),
	"The thick, twisting vines drop down into the water from low-"+
	"hanging branches above. You can see the shadowy outlines of "+
	"the trees that support the vines, but nothing more is visible "+
	"through the thick blanket of mist. The vines are so thick that "+
	"sometimes you can't maneuver through them without cutting them "+
	"apart.\n");    


    add_fexit(CORAMAR+"f60", "northwest", 0);
    add_fexit(CORAMAR+"f74", "southeast", 0);

}   