/* File: /d/Shire/common/eastroad/mpath4 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
	"You are walking on a narrow path by the river Bruinen. "+
	"As you turn northeast you leave the Trollshaws "+
	"behind you. The area around you is becoming "+
	"solid rock with only a muddy path by the river side.\n"
    );


    add_item(({"narrow path", "path" }),
        "This is a small muddy path by the river Bruinen. The path follows \n"+
        "the river upstream.\n"  
    );
    add_item(({"river","bruinen","Bruinen"}),
        "This is the mighty river Bruinen, though it is getting smaller \n"+
        "in size as you get closer to the Misty Mountains. The river is \n"+
        "very cold, because the water is newly melted from the Misty Mountains.\n"
    );
    
    add_item(({"mud"}),
            "This is a brown sticky mud. It's obviously made by the \n"+
            "water from the Bruinen.\n"
    );

    
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
	"You notice that the water is freezing cold, " +
	"hence, you would not even try it.\n");

   
    NORTHEAST("mpath5");
    SOUTHWEST("mpath3");
}
