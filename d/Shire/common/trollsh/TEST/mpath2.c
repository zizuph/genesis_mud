/* File: /d/Shire/common/eastroad/mpath2 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("On the Great East Road near the Trollshaws");
    set_long("Walking on the Great East Road, by the river " +
		"Bruinen, you notice to the west is the great forest " +
		"Trollshaws. It is said that the forest is packed with " +
		"trolls. Up the path you notice some giant footprints " +
		"in the mud. The footprints come from the forest and " +
		"head down towards the riverbank.\n");
    add_item(({"path", "path", "great east road", "road"}),
        "This is a road by the river Bruinen. The road follows " +
        "the river upstream.\n");
    add_item(({"river","bruinen","water"}),
        "This is the mighty river Bruinen. It doesn't seem " +
        "possible to cross here, maybe further south.\n");
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
        "You notice that the water is freezing cold, hence, you " +
        "would not even try it.\n");

    add_item(({"prints","footprints"}),
	"@@exa_prints@@");

    NORTH("mpath3");
    SOUTH("mpath1");
}

string
exa_prints()
{
    if (TP->query_skill(SS_TRACKING) +
        TP->query_skill(SS_AWARENESS) + random(50) > 150)
	return "They look like footprints from a troll. It seems like the\n"
             + "troll had a big fight here, and was victorious. It\n"
             + "seems like the troll had been dragging something after it.\n";
    else if (TP->query_skill(SS_TRACKING) + TP->query_skill(SS_AWARENESS) > 60)
        return "You are pretty sure they are troll prints!\n";
    else
	return "They look like large footprints!\n";

}
