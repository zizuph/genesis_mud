/*
 * Took out seagul. Seagulls aren't this far inland
 * -- Finwe August, 2005
 */

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

void add_stuff();

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "flat field";
    grass = "blue-green";
    extraline = "The road to Annuminas was once a fair road, "+
    "paved with solid, well-rounded stone.  North it leads to "+
    "the ruined city, and south it dwindles into a flat field.";
    add_item(({"road","fair road"}),
      "Sometimes between the clumps of blue-green grass, "+
      "you can see the traces of stone that marked the boundaries "+
      "of this wide road.\n");
    add_item(({"solid stone","stone","well-rounded stone"}),
      "Between the clumps of grass you notice the fine granite "+
      "of the road- sadly it has been covered up by the grass in "+
      "most places.\n");
    add_item(({"city","ruined city","annuminas"}),
      "A great fog obscures your view of the ruined city of "+
      "Annuminas.\n");
    add_item(({"flat field","field"}),
      "It is a flat field, colored blue-green from the grass that "+
      "flourishes there.\n");
    add_exit(EVENDIM_DIR + "ev7","south",0,1);
    add_exit(EVENDIM_DIR + "ev9","north","@@leave_shire@@");
    set_noshow_obvious(1);
    add_stuff();
}

void
add_stuff()
{
/*
    object animal;
    if(!present("seagull"))
    {
	animal = clone_object(EVENDIM_DIR + "npc/gull");
	animal->move(TO);
    }
*/
}

void
reset_shire_room()
{
    add_stuff();
}



void leave_shire()
{
    write("You cross the North Farthing border and leave the Shire.\n");
}