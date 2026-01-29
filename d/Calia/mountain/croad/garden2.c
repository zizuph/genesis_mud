// ROOM:  palace garden 2

    /* Calia Domain

    HISTORY

    [96-02-23] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN2.DOC].

    PURPOSE

    This room is one of 14 garden rooms surrounding Calia palace.  See comments
    in Room 1 for area details.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include "crdefs.h"
#include "cant_plant.c"

// FUNCTIONS

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(plant_seed, "plant");    /* function in "cant_plant.c" */

    }

// ROOM DEFINITION

void
create_room()

    {

    /*  DESCRIPTION  */

    set_short("Calia Palace Gardens, south side");

    set_long("You stand on a path that leads through the palace " +
        "gardens.  On either side of you are tall, graceful " +
        "willows that provide shade and seclusion for anyone who might " +
        "wish to spend a few moments here in quiet reflection.  " +
        "A bit of mist drifts into the garden between the trees, " +
        "and it swirls about your feet as you walk.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden1", "southeast", 0);
    add_exit(CROAD + "garden3", "northwest", 0);

    /*  ITEMS  */

    add_item(({"garden","gardens"}),
        "This section of the garden is planted with stately rows " +
        "of trees that shade the path surrounding the palace.\n");

    add_item(({"path","stones"}),
        "The stones are freshly hewn and show no signs of wear.  " +
        "They lead further into the willows to the northwest, " +
        "and back toward the front of the palace to the southeast.\n");

    add_item(({"willow","willows","trees","tree"}),
        "These are weeping willows, planted in memory of the many " +
        "warriors who gave their lives on the mountainside.  " +
        "Between them you can catch a glimpse of the mist that " +
        "perpetually surrounds the upper levels of Mt. Kyrus.\n");

    add_item(("palace"),
        "The walls of the palace are made of sparkling crystal, " +
        "and you can see no trace of nails, mortar, or any other " +
        "kind of fastening.  You get the impression that the palace " +
        "was carved from one immense, flawless gemstone.\n");

    add_item(("mist"),
        "The mist ebbs and flows in between the trees like a rising " +
        "and falling tide along a craggy coast.  Farther out in the " +
        "distance you can see meandering currents that part and deflect " +
        "as they flow past the mountain.\n");

    }
