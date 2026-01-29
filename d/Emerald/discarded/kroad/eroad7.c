/*
 * eroad7.c
 * Kahlen Road
 * by Alaron September 1, 1996
 * Noiseroom added by Jaypeg - 13th Feb 97
 */

#include "defs.h"

inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";


void
create_ov_road()
{
    set_short("Coastal road near a stone bridge");
    set_long("   You stand at the base of an enormous stone bridge. The "+
	     "bridge seems to drip fluidly out of the cliff face and "+
	     "sweep across the open channel to the northern cliff face. The "+
	     "construction of the bridge is smooth and fluid. The road "+
	     "continues to the east and west from here. The southern edge "+
	     "of the road is bordered by low greenery and vegetation which "+
	     "eventually give way to an enormous forest. The sounds of "+
	     "churning water and waves splashing can be heard echoing up "+
	     "from the channel far below.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "cliff face", "cliff faces", "north"}),
	     "The cliffs rise majestically and nearly vertically out of "+
	     "the ocean channel below to stand in stark contrast with "+
	     "the deep blue color of the sea water. Seemingly dripping out "+
	     "of the cliff face is an incredible work of engineering - "+
	     "A massive stone bridge carved so finely and smoothly that it "+
	     "almost appears to be flowing liquid.\n");

    add_item( ({"bridge", "stone bridge", "massive stone bridge"}),
	     "The massive stone bridge which crosses the channel to the "+
	     "north is a marvel of engineering and construction. It is "+
	     "cut from a single piece of heavy stone. The curves, contours "+
	     "and lines of the bridge have all been expertly carved and "+
	     "design to create the illusion that the bridge is actually "+
	     "flowing liquid. As you sway back and forth, testing the effect, "+
	     "you suddenly end up fighting off a bout of vertigo.\n");


    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "overgrown greenery", "greenery"}),
	     "The bushes and vegetation bordering the dirt road seem "+
	     "to creep up on it, almost reaching for the moisture which "+
	     "is collecting on the road closer to the cliffs. Among the "+
	     "scattered vegetation and greenery, you recognize several "+
	     "flowers and weeds.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "Among the greenery surrounding the road, there are several "+
	     "pretty, sweet-smelling flowers. In addition, there "+
	     "are many recognizable kinds of weeds and vines.\n");

    add_exit(PATH + "eroad8", "east", 0, 1);
    add_exit(PATH + "bridge", "north", 0, 1);
    add_exit(PATH + "eroad9", "west", 0, 1);

}
