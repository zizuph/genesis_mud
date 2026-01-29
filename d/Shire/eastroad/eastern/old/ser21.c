#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser20","west",0,1
#define EXIT2 ERE_DIR + "ser7","southwest",0,1

void
create_er_room()
{

    area = "in";
    areaname = "the Misty Mountains";
    land = "Eriador";
    areatype = 5;
    areadesc = "trail";

    extraline ="You are surrounded by the almost vertical sides "+
    "of the mountains as you make your way along the narrow "+
    "trail through them.  You can vaguely make out the River "+
    "Bruinen to the west.  To the east, lies the "+
    "Wilderland.  It is impossible to get across the mountains "+
    "here to your east, however, due to a pile of large rocks "+
    "that looks impossible to move.";
    add_item(({"peaks","snow-tipped peaks"}),"The peaks of the "+
      "mountains are covered with snow.  You hope that you can "+
      "find a way to go between them and will not have to go "+
      "over them.\n");
    add_item(({"pile","rocks","large rocks"}),"The pile of rocks is "+
      "in the middle of the trail.  After examining the rocks, you "+
      "come to the conclusion that almost all of them are too heavy "+
      "to be moved.\n");
    add_item(({"trail","rocky trail"}),"The trail is narrow and winding "+
      "and comes to a dead-end to the east due to a rockslide.\n");
    add_item(({"mountains","Misty Mountains"}),"The mountains "+
      "are not far from you to the southwest, and a journey "+
      "that way would probably be very long and tiring.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
}
