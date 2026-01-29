#include "defs.h"

inherit "/d/Shire/common/lib/rom";

create_rom()
{
    set_short("Road north of town center");
    set_long(
	    "You are walking on a road in Bree going towards the Bree-Hill. "+
	    "More holes can be seen in the ground and more houses as you " +
        "come closer to the living area of the Bree inhabitants. The " +
        "path is quite steep, and you can feel it in your legs trying " +
        "to walk up this slope. North of here, the house of the Gardener " +
        "in Bree can be spotted. It is a rather large place with a " +
        "big garden outside it. The path continues north towards the " +
        "hill and south towards the center of Bree.\n");

    add_exit(BREE_DIR + "brroad1", "southwest", 0, 1);
    add_exit(BREE_DIR + "hill2", "northeast", 0, 6);


    add_item(({"garden"}),
	    "It is a bit difficult to see the extent of the garden since there "+
	    "is some trees covering your whole view up there.\n");

    add_item(({"trees", "tree"}),
	    "From what can be spotted it looks like oak trees, and they " +
        "look very old.\n");

    add_item(({"house"}),
	    "A little further north this house has a well kept garden. You " +
        "guess that the person owning the house knows a whole lot about " +
        "gardens and trees since it looks so beautiful.\n");

    add_item(({"slope", "path", "road"}),
	    "The slope is quite steep here, but you as you come closer to " +
        "the top the path is getting less steeper further up.\n");
}
