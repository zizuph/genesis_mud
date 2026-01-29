/*
 *	/d/Gondor/rohan/road/er4.c
 *
 *	Rewritten by Olorin, 25-Nov-1996
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

static object  Guard;

public void
create_roads() 
{
    set_street("large, stonelaid, dusty road");
    set_where("southeast");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("White Mountains");
    set_vegetation("long, light green, juicy grass");
    set_extraline("North, west and east the ground is covered by " 
      + Vegetation + ". The " + Mountain + " make the southern "
      + "horizon look like the blade of a giant saw. The road "
      + "runs between the mountains to the south and the plains "
      + "to the north from southeast to northwest.");

    add_item( ({ "mountains", "white mountains", "ered nimrais", }),
	"The snow-covered tops of the White Mountains or Ered Nimrais"
      + " are rising south of the road. Between the mountains and the"
      + " road are smaller hills, some covered with green forests, and"
      + " between them open many vales.\n");
    add_item( ({ "road", "west road", }),
        "The road skirts the northern foothills of the White"
      + " Mountains, running from the southeast to the northwest"
      + " just south of the wide plains of Rohan.\n");
    add_item( ({"plains", "plains of rohan", }),
        "The plains of Rohan stretch as far as one can see north of"
      + " the road, covered by " + Vegetation + ".\n");
    add_item( ({"hills", "foothills", "vales", }), 
        "Between the road and the mountains there are the northern"
      + " foothills of the White Mountains, gentle hills with deep"
      + " vales opening between them.\n");

    add_exit(ROH_DIR + "plains/e11", "north",     0, 3);
    add_exit(ROH_DIR + "plains/d12", "east",      0, 3);
    add_exit(ROH_DIR + "road/er5",   "southeast", 0, 2);
    add_exit(ROH_DIR + "road/er3",   "northwest", 0, 2);

    reset_room();
}

public void
reset_room()
{
    Guard = clone_npc(Guard, ROH_DIR + "npc/roadguard");
}
