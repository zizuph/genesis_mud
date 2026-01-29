/* File: /d/Shire/common/eastroad/mpath3 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
        "You are walking on a narrow path by the river Bruinen. "+
        "To the west is the great forest Trollshaws. It is "+
        "said that the forest is packed with trolls. @@exa_bark@@\n"
    );

    add_item(({"narrow path", "path" }),
        "This is a small muddy path by the river Bruinen. The path follows \n"+
        "the river upstream.\n"  
    );
    add_item(({"river","bruinen","Bruinen"}),
        "This is the mighty river Bruinen, though it is getting smaller\n"+
        " in size as you get closer to the Misty mountains. The river is\n"+
        "very cold, because the water is newly melted from the Misty Mountains.\n"
    );
    
    add_item(({"mud"}),
            "This is a brown sticky mud. It's obviously made by the\n"+
            "water from the Bruinen.\n"
    );

       
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
	"You notice that the water is freezing cold, " +
	"hence, you would not even try it.\n");

    add_item(({"marks","barque","bark","tree"}),
	"@@exa_barque@@");

    NORTHEAST("mpath4");
    SOUTH("mpath2");
}


string
exa_bark()
{
      if (TP->query_skill(SS_AWARENESS) >30)
            return "On one of the trees you notice some marks on the bark.\n";  
         else
            return "The river is getting smaller the closer you get to \n"+
                   "the Misty Mountains.\n"; 
                             
}
string
exa_barque()
{
    if (TP->query_skill(SS_TRACKING) + WIS(TP) + INT(TP) > 300 - random(50))
  return "The marks in the bark seem to have been made by a club. "+
      "Apparently some fighting has taken place here, perhaps even some "+   
      "trolls were involved, as there is known to be a LOT of trolls "+
      "living in the forest.\n";
 else
   return "Just some odd markings in the bark.\n";
}


/* This is the original code from 61-65 I found here. I'm replacing the
 * string, if you hate it, you can replace what you had here originally :)
 * Mayhem.
	return "It looks like marks after a club. It have obviously been "
             + "some fighting here, probably after some troll, since the "
             + "forest is know to inhabit a LOT of trolls. \n";
    else
	return "It looks like large marks in the bark! \n";
 */
