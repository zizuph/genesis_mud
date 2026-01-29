
/*
 * Gardenroom Base File
 *
 * To be inherited by garden rooms
 *
 * Copyright (c) Marisol Ramos August 1997.
 * This file is called by the garden rooms and contains
 * generic information.
 *
 */
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell.c";
#include "defs.h"
inherit HS;

#include <stdproperties.h>

#include "/d/Emerald/marisol/ovejuno/garden/gtells.h"
#include "/d/Emerald/sys/terrain_types.h"
#include "/d/Emerald/sys/properties.h"
#define CASTLEG_HERBS ({\
HERB_DIR + "milky_rose.c",\
HERB_DIR + "scarlet_rose.c",\
HERB_DIR + "ebony_rose.c",\
HERB_DIR + "grave_fl.c",\
HERB_DIR + "borage.c",\
HERB_DIR + "marsh_mallow.c",\
HERB_DIR + "primrose.c",\
HERB_DIR + "selfheal.c",\
GONDOR_HERBS + "bean_fava.c",\
GONDOR_HERBS + "bean_green.c",\
GONDOR_HERBS + "blackberry.c",\
GONDOR_HERBS + "chervil.c",\
GONDOR_HERBS + "garlic.c",\
GONDOR_HERBS + "laurel.c",\
KRYNN_HERBS  + "dandelion.c",\
})

#define CGARDEN_LOCATIONS ({\
"ground", "here", "bushes", "trees"})

void
create_emerald_garden()
{
}
nomask void
create_emerald_room()
{

    int i;

    set_short("An old ruined garden");
    add_item("garden",
        "The garden seems to have been abandoned for many years and "+
        "needs a lot of gardening to recover its former beauty. A tall "+
        "hedge of rhododendrons surrounds the garden. Another tall "+
        "hedge surrounds a fountain. Above the garden in a northward "+
        "direction looms the castle of Talbarion. For some "+
        "reason you feel observed.\n");

    add_item("hedge",
        "This is a tall rhododendron hedge that blocks your view "+
        "outside the garden.\n");

    add_item("rhododendron",
        "Emerald leaves and bright pink flowers comprise the "+
        "tall hedge that surrounds the garden.\n");

    add_item(({"pink flowers", "bright pink flowers"}),
        "The bright pink petals exude a honeyed aroma like honey "+
        "mead.\n");
    add_item(({"weeds", "yellow flowers"}),
        "These are dandelions, also known as Lion's Tooth. These are "+
        "the worst weeds that a garden can get. They have jagged "+
        "leaves, that resemble teeth, and yellow flowers.\n");

    add_item(({"ground", "path"}),
        "The path's ground is covered with green grass that have "+
        "overgrowed outside the path bounderies. Here and there you, "+
        "see peeking out from the grass, yellow flowers and other more "+
        "exotic flora.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);


    set_up_herbs((this_object()->select_herb_files(CASTLEG_HERBS)),
    CGARDEN_LOCATIONS, 3);

    set_tell_time(100);
    for(i = 0; i <4; i++)
    {
     add_tell(GTELLS[random(sizeof(GTELLS))]);
    }
    create_emerald_garden();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}
