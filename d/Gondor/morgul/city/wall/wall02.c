#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The Morgul Gate lies west of here. The wall "
      + "continues east to the northeast tower of the city. To the "
      + "north, you can see the dark vale of the Morgulduin and the "
      + "steep cliffs of the mountains rising behind it. Looking down "
      + "into the city to the south you see the great tower of Minas "
      + "Morgul dominating the view."); 
    set_road(1);
    set_side("north");

    add_tower();
    add_view_north();

    add_exit(MORGUL_DIR + "city/wall/wall03","east","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall01","west","@@check_exit",1);
}
