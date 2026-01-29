/* Gardenroom Base File
 *
 * To be inherited by garden rooms
 * 
 * To be used for Herb_Garden
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

#include "/d/Emerald/marisol/ovejuno/village_OV/herb_tells.h"
#include "/d/Emerald/sys/terrain_types.h"
#include "/d/Emerald/sys/properties.h"
#define GARDEN_HERBS ({ \
HERB_DIR + "apoth_rose.c", \
HERB_DIR + "bee_balm.c", \
HERB_DIR + "loyol.c", \
HERB_DIR + "meadowsweet.c", \
HERB_DIR + "red_yarrow.c", \
HERB_DIR + "lavander.c", \
GONDOR_HERBS + "basil.c", \
GONDOR_HERBS + "bean_black.c", \
GONDOR_HERBS + "strawberry.c", \
KRYNN_HERBS + "dandelion.c"})
     
#define HERB_LOCATIONS ({"here", "ground"})

void
create_emerald_garden()
{
}
nomask void
create_emerald_room()
{

    int i;

    set_short("A herb garden");
    add_item("garden",
        "The garden is well tended by the sage femme. A variety of "+
        "herbs are cultivated row after row in this garden.\n");

    add_item("herbs",
        "Common herbs like grass and dandellions mix with more "+
        "rare herbs from all over Emerald.\n");

    add_item("ground",
        "The ground is covered with uneven cut grass. Chicken prints   "+
        "appear here and there. Among the blades of grass, "+
        "yellow dandellions and other more exotic flora.\n");

    add_item("grass",
        "Is green and lush.\n");

    add_item("dandellions",
        "This is a common weed in any garden. They are hard to get rid "+
        "and their roots are long and difficult to extirpate. But "+
        "it have beautiful yellow flowers.\n");
    

        add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);
   
        set_up_herbs((this_object()->select_herb_files(GARDEN_HERBS)),
        HERB_LOCATIONS, 3);
   
        set_tell_time(100);
        for(i = 0; i <4; i++)
        {    
         add_tell(HERBTELLS[random(sizeof(HERBTELLS))]);
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
