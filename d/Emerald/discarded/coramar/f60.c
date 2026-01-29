/*
 * f60
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

    set_long("   You are standing knee-deep in ice-cold water from "+
	"a mountain spring of some kind. The stream is bordered on "+
	"both sides by the enormous trees which populate this strange, "+
	"mysterious forest. The trunks are so close together that you "+
	"could not fit through them to try and leave the stream's "+
	"powerful, icy current. The current is strong enough "+
	"that you are continually resisting its attempts to knock "+
	"you over and sweep you downstream. Thick, twisted vines drop "+
	"down into the running water from branches so low that you have "+
	"to duck to avoid them. The thick bank of mist swirls around the "+
	"river, hiding the rest of the forest behind a sheen of dark "+
	"grayness. The river continues downstream to the southeast. On "+
	"the east bank, you can see a small section of the surrounding "+
	"trees break and become a small path leading to relatively dry "+	
	"land.\n\n");

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

    add_item( ({"bank", "riverbank", "east", "stream bank"}),
	"The east bank of the stream seems to have a small break "+
	"in the trees which leads up and away from the stream, dissappearing "+		"behind the veil of thick gray mist.\n");

    remove_item("vines");
    add_item( ({"vines", "thick vines", "twisting vines",
	"thick twisting vines"}),
	"The thick, twisting vines drop down into the water from low-"+
	"hanging branches above. You can see the shadowy outlines of "+
	"the trees that support the vines, but nothing more is visible "+
	"through the thick blanket of mist. The vines are so thick that "+
	"sometimes you can't maneuver through them without cutting them "+
	"apart.\n");    


    add_fexit(CORAMAR+"f59", "northwest", 0);
    add_fexit(CORAMAR+"f75", "east", 0);
    add_fexit(CORAMAR+"f61", "southeast", 0);

}   