/* File: /d/Shire/common/eastroad/mpath4 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

#define GER "/d/Shire/eastroad/eastern/"

create_rom()
{

    set_short("On the Great East Road near the Trollshaws");
    set_long("You are walking on the Great East Road near the " +
		"river Bruinen. As you turn northeast you leave the " +
		"Trollshaws behind you. The area around you is becoming " +
		"solid rock with only a muddy path by the river side.\n");

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

    add_item(({"mud"}),
        "This is a brown sticky mud. It's obviously made by the " +
        "water from the Bruinen.\n"); 
    add_exit(GER + "imladris_connect", "north");
    SOUTHWEST("mpath3");
}
