/* This file is /d/Gondor/rohan/farm/road/garden1.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

int     nr = 1 + random(3);
object *rabbit = allocate(nr);

public void
create_area_room() 
{
    set_areadesc("garden");
    set_areatype(0);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("");
    set_forest("");
    set_extraline("The garden must have been magnificent, full of flowers, herbs, "
      + "and fruit trees. But now it looks quite neglected. To the northeast is "
      + "the yard.");
    add_exit(FARM_DIR + "road/yard1", "northeast", 0);

    set_up_herbs( ({ SHIRE_HERB_DIR + "parsley", SHIRE_HERB_DIR + "pawnrose",
		     HERB_DIR + "garlic", HERB_DIR + "tarragon", 
		     HERB_DIR + "chervil", HERB_DIR + "curugwath", }), 
		  ({ "garden", "ground", }), 2);

    add_item("garden",BS("It must have a wonderful place, but now "
      + "there is hardly anything useful left in it.\n"));
    add_item("flowers",BS("Roses need a lot of care. The flower beds are "
      + "overgrown with weeds and herbs, and there are no flowers to be "
      + "seen anymore.\n"));
    add_item("herbs",BS("All the herbs you can see at a first glance are "
      + "useless. But perhaps you will find something of value if "
      + "you have a closer look.\n"));
    add_item("vegetables",BS("Quite a few different kinds of vegetables "
      + "must have been growing here. Obviously a lot of animals found "
      + "that out long before you did. They left nothing for you.\n"));
    add_item("fruits",BS("Birds and other animals seem to have eaten all "
      + "fruits long ago.\n"));
 
    reset_room();
}

public void
clone_rabbit(int n)
{
    int   i = n-1;

    if (!objectp(rabbit[i]))
    {
	rabbit[i]=clone_object(NPC_DIR + "rabbit");
	rabbit[i]->set_restrain_path("/d/Gondor/rohan/farm/road");
	rabbit[i]->move_living("down", TO);
    }
    n--;
    if (i)
        set_alarm(itof(10 + random(30)), 0.0, &clone_rabbit(n));
}

public void
reset_room()
{
    ::reset_room();

    set_alarm(4.0, 0.0, &clone_rabbit(nr));
}
