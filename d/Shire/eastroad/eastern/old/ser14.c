#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser13","southeast",0,1
#define EXIT2 ERE_DIR + "ser6","northwest",0,1

void
create_er_room()
{

    area = "in";
    areaname = "the Misty Mountains";
    land = "Eriador";
    areatype = 5;
    areadesc = "trail";

    extraline ="This trail does not look like it is used very much.  "+
    "It is very narrow and is covered with rocks and snow.  To the "+
    "southeast is another part of the trail that does not look "+
    "much better, but to the northwest there is a path that is "+
    "somewhat wider.";
    add_item(({"trail","ground"}),"The path here is among some of the "+
      "worst that you have ever travelled on, and you can hardly wait "+
      "to be clear of it.\n");
    add_item(({"peaks","snow-tipped peaks"}),"The peaks of the "+
      "mountains are covered with snow.  You hope that you can "+
      "find a way to go between them and will not have to go "+
      "over them.\n");
    add_item(({"mountains","Misty Mountains"}),"The mountains "+
      "are just ahead of you to the northeast, and a journey "+
      "that way would probably be very long and tiring.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
}
