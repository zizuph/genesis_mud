#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is the western part of the great Morgul Gate. "
      + "To the north, you can see the dark vale of the Morgulduin and "
      + "the steep cliffs of the mountains rising behind it. Looking "
      + "down into the city to the south you see the great tower of "
      + "Minas Morgul dominating the view. There is a flight of stairs "
      + "here leading down into the streets of the city."); 

    set_road(1);
    set_side("northwest");

    add_tower();
    add_view_north();
    add_stairs_down();

    add_exit(MORGUL_DIR + "city/wall/wall01","east","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall19","southwest","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/mmr1","down","@@block_npc",2);
}
