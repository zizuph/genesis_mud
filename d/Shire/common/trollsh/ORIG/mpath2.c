/* File: /d/Shire/common/eastroad/mpath2 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
	"You are walking on a narrow path by the river Bruinen. "+
        "To the west is the great forest Trollshaws. It is "+
        "said that the forest is packed with trolls. While you walk "+
        "up the path you notice some giant footprints in the mud. "+
	"The footprints come from the forest and head down towards "+
        "the riverside.\n"                       
    );

    add_item(({"narrow path", "path" }),
        "This is a small muddy path by the river Bruinen. The path follows \n"+
        "the river upstream.\n"  
    );
    add_item(({"river","bruinen"}),
        "This is the mighty river Bruinen. The river is very cold,\n"+
        "because the water is newly melted from the Misty Mountains.\n"
    );
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
	"You notice that the water is freezing cold, " +
	"hence, you would not even try it.\n");


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
