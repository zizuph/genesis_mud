/*
 * f59
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

    set_long("   You are at a turning-point in a narrow, "+
	"clear stream. It descends from the mist at higher elevations "+
	"from the northeast and banks to the southeast. Thick, twisting "+
	"vines drop down into the stream from low-hanging branches "+
	"above, making the passage southeast through the stream difficult "+
	"to navigate. As you duck under the branches and splash through "+
	"the water, the icy temperature of the mountain spring water "+
	"sends a chill through your body. The thick cloud of mist hovering "+
	"low over the surface of the water makes navigation even more "+
	"difficult. An icy, mountain breeze blows into the area from "+
	"the northwest, shaking the vines and branches. It is quiet "+
	"here with the exception of the sound of the water running "+
	"across the surface of the smooth rocks beneath.\n\n");

    add_item( ({"water", "stream", "brook" , "river", "runoff", "spring"}),
	"The water from the mountain spring is as cold as ice. The "+
	"water is clear and looks as though it would taste "+
	"wonderfully refreshing on a hot day. The surface of the water "+
	"is cluttered by fallen leaves and the hanging vines. It descends "+
	"from the mountains from the northeast and banks southeast to "+
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


    add_fexit(CORAMAR+"f22", "northwest", 0);
    add_fexit(CORAMAR+"f60", "southeast", 0);

}   