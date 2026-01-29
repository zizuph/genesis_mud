/* File: /d/Shire/common/eastroad/mpath7 */

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";

create_rom()
{

    set_short("Narrow path by the river Bruinen");
    set_long(
      "You are still walking on a narrow path by the river Bruinen. \n"+
      "You have reached the foot of the mountains. Now you can clearly "+
      "see the true size of the Misty Mountains. The mountains "+
      "stretch thousands of feet up into the sky.\n"
    );


    add_item(({"narrow path", "path" }),
      "This is a small stony path by the river Bruinen. The path follows \n"+
      "the river upstream.\n"  
    );
    add_item(({"river","bruinen","Bruinen"}),
      "This is the mighty river Bruinen. Thow it is getting smaller\n"+
      "in size as you get closer to the Misty Mountains. Here the "+
      "main river is joined by many small streams. The water looks very "+
      "cold and you can see a few bits of ice in the river.\n" 
    );
    add_item(({"mountain","misty mountains","misty mountain"}),
      "You are astonished by the sight of the Misty Mountains.\n"+
      "The mountains stretch as far as you can see to both the east"+   
      "and west. You can't even see the top of the mountains.\n"
    );
    add_item(({"rock"}),
      "You are getting very close to the Misty Mountains, so the\n"+
      "path is on solid rock now.\n"
    );


    add_neg(({"swim", "enter", "dive", "jump"}),
      "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
      "You notice that the water is freezing cold, " +
      "hence, you would not even try it.\n");



    add_exit("/d/Shire/common/trollsh/mpath6", "southwest", 0, 1);
#ifndef RHOVANION_CLOSED
    add_exit("/d/Shire/common/rhovanionlink", "northeast",0);
#else
    add_exit(ERE_DIR +"misty_link", "northeast");
#endif
}


