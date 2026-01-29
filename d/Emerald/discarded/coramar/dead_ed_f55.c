/*
 * f55
 * Coramar Forest
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"

inherit BASEFOREST;

void
create_forest()
{  
    set_long("   You find yourself at a junction of several forest "+
	"trails. Knee-deep in the icy waters of a mountain spring, you "+
	"can see paths leading off to the east and southwest, with "+
	"the running water coming from a northwesterly direction. Low-"+
	"hanging branches drop thick, twisted vines down into the "+
	"strong, icy current of the stream, making it difficult to "+
	"maneuver through the area. The stream continues slightly "+
	"southeast here and then disappears down a hole and continues "+
	"to run underground from that point.\n\n");


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

    add_item("hole",
	"This is where the mountain spring disappears. It is a large "+
	"hole in the ground surrounded by thick foliage and "+
	"vegetation. The echoing sound of a waterfall bubbles up from "+



    add_fexit(CORAMAR+"f74", "northwest", 0);
    add_fexit(CORAMAR+"f73", "east", 0);
    add_fexit(CORAMAR+"f54", "southwest", 0);
}
