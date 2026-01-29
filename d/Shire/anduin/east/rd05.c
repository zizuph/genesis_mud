/*
 * Road in western vales of Anduin.
 * By Finwe, June 2001
 *
 * Changed east exit to connect to Mirkwood
 * Varian, 2015
 */
 
#pragma strict_types
 
#include "/d/Shire/sys/defs.h"
#include "local.h"

inherit VALE_BASE;

#define MIRK_DIR "/d/Shire/mirkwood/"
void
create_vale_room()
{
    set_area("on the western edge of");
    set_areaname("Mirkwood Forest");
    set_land("Wilderland");
    set_vbfc_extra(road_desc2);
    add_my_desc("It leads east into Mirkwood Forest and west towards " +
        "the Anduin and the Misty Mountains.\n");

    add_item(({"forest", "mirkwood", "mirkwood forest", 
            "greenwood the great", "wood", "great wood", "taur e-ndaedelos"}),
        "The Mirkwood Forest, once known as Greenwood the Great, " +
        "is an ancient forest that runs the width of Middle-earth. " +
        "It is dark and evil where very few travellers, except " +
        "for the very brave, dare to enter.\n");
      

    set_add_river_far();
    set_add_misty_far();

    add_exit(EAST_DIR + "rd04", "west");
    add_exit("/d/Gondor/rhovanion/mirkwood/oldroad/r01.c", "east", "@@block_me@@");

    reset_shire_room();

}

int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

        write("This is the infamous Mirkwood forest, whose mere name ignites " +
            "fear and caution into the bravest of hearts. You find that " +
            "the road is currently closed, yet rumours abound that it " +
            "could be open once more someday quite soon.\n");
    return 1;
}

void
reset_shire_room()
{
/*
    object quiver;

        if (!present("quiver",TO))
    {
        quiver = clone_object("/d/Shire/scav_hunt/quiver");
        quiver->add_prop(OBJ_I_HIDE, 10 + random(10));
        quiver->move(TO);
    }
*/
}

