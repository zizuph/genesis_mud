/* File: /d/Shire/common/eastroad/mpath5 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
        "You are still walking on a narrow path by the river Bruinen. \n"+
        "North you can see that the river is divided into many small brooks. \n"+
        "The path is no longer muddy as there is only solid rock under "+
	       "your feet. \n"
    );


    add_item(({"narrow path", "path" }),
        "This is a small stony path by the river Bruinen. The path follows \n"+
        "the river upstream.\n"  
    );
    add_item(({"river","bruinen","Bruinen"}),
        "This is the mighty river Bruinen, though it is getting smaller\n"+
        "in size as you get closer to the Misty Mountains. The river is\n"+
        "very cold, because the water is newly melted from the Misty Mountains.\n"
    );
    
    add_item(({"rock"}),
            "You are getting very close to the Misty Mountains, so the\n"+
            "path is only solid rock now.\n"
    );

    
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
	"You notice that the water is freezing cold, " +
	"hence, you would not even try it.\n");

    

    NORTHEAST("mpath6");
    SOUTHWEST("mpath4");
}
