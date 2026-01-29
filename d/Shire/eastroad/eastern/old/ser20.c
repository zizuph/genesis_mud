#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser19","west",0,1
#define EXIT2 ERE_DIR + "ser21","east",0,1

void
create_er_room()
{

    area = "in";
    areaname = "the Misty Mountains";
    land = "Eriador";
    areatype = 5;
    areadesc = "trail";

    extraline ="The trail is very steep here, and you wonder how "+
    "you are ever going to complete your journey, especially "+
    "when you feel the cold air and gaze at the snow-tipped "+
    "peaks.  The River Bruinen is flowing past you to the "+
    "can see the rough trail going endlessly on before you to the "+
    "northwest.";
    add_item(({"river","River Bruinen","water"}),"The water "+
      "looks cold, wet and filled with all sorts of life that "+
      "you would prefer not to think about.\n");
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
