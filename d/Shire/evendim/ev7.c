inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev11","east",0,1
#define EXIT2 EVENDIM_DIR + "ev8","north",0,1
#define EXIT3 GREEN_DIR + "vill1","west",0,1
#define EXIT4 EVENDIM_DIR + "ev6","southeast",0,1

void add_stuff();

void
create_er_room()
{
    FIXEUID;
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "flat field";
    grass = "blue-green";
    extraline = "This field here is grassy and flat, though there several "+
    "hills rising to the southeast. You are standing at an old meeting "+
    "of ways, where a small track coming from the heart of the Shire "+
    "winds up from the southeast and flows west into a small village. "+
    "Meanwhile to the north you can follow an ancient trail which " +
    "runs straight towards the abandoned city of Annuminas.";
    add_item(({"track", "path"}),
      "This winding track seems to come from a village to the west " +
      "before it leads back southeast, towards the heart "+
      "of the Shire.\n");
    add_item(({"trail","road","paved road"}),
      "The old trail is actually a paved road fallen into great "+
      "disrepair for several centuries.\n");
    add_item(({"field"}),"The field stretches north, east, and "+
      "west for several hundred yards before the hills rise up "+
      "again.\n");
    add_item(({"meeting","old meeting","old meeting of ways","crossroads","crossroad"}),
      "Here an old partially paved road leading north meets "+
      "a battered down trail going southeast. West a path leads "+
      "toward the hobbit village of Greenfields.\n");
    add_item(({"village","greenfields"}),
      "Just a short distance to the west, you can make out the small "+
      "hobbit village of Greenfields. If you would like to visit the "+
      "village, there is a small path leading west from these crossroads " +
      "which will take you there.\n");
    add_item(({"annuminas","city","ruins"}),
      "The crumbling ruins of the city of Annuminas is not visible here. " +
      "However, it is likely that the ancient remnants of the highway that " +
      "leads north from this crossroad will take you there.\n");
    // add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);
    set_noshow_obvious(1);
    add_stuff();
}

void
add_stuff()
{
    object animal;
    if(!present("ant"))
    {
	animal = clone_object(EVENDIM_DIR + "npc/ant");
	animal->move(TO);
    }
}

void
reset_shire_room()
{
    add_stuff();
}
