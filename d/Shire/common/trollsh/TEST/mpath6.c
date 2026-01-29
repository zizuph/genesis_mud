/* File: /d/Shire/common/eastroad/mpath6 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

#define GER "/d/Shire/eastroad/eastern/"

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
	"You are still walking on a narrow path by the river Bruinen. "+
	"The river is joined here by many brooklets. "+
	"One of the streams is clearly bigger than the others, "+
        "and it is obvious that the path follows the larger brooklet. \n"
    );


    add_item(({"narrow path", "path" }),
        "This is a small stony path by the river Bruinen. The path follows \n"+
        "the river upstream.\n"  
    );
    add_item(({"river","bruinen","Bruinen"}),
        "This is the river Bruinen, though it is getting smaller \n"+
        "as you get closer to the Misty Mountains. "+
        "Here the main river is joined by many brooklets. "+
        "The water looks very cold and you can see a "+
        "few ice crystals in the river.\n");

    
    add_item(({"rock"}),
            "You are getting very close to the Misty Mountains, so the\n"+
            "path is only solid rock now.\n"
    );

    
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
	"You notice that the water is freezing cold, " +
	"hence, you would not even try it.\n");

   
    add_exit(GER + "imladris_connect", "south");
    SOUTHWEST("mpath5");
}
