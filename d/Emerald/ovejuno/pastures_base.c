/* Pasture room Base File
 *
 * To be inherited by pasture rooms
 *
 * To be used for Pasture_rooms
 *
 * Copyright (c) Marisol Ramos April 1998.
 * Modified by Marisol (08/05/98)
 * This file is called by the pasture rooms and contains
 * generic information.
 *
 */

#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell.c";

#include "defs.h"
inherit HS;

#include "/d/Emerald/sys/terrain_types.h"
#include "/d/Emerald/sys/properties.h"

void
create_emerald_pasture()
{
}

nomask void
create_emerald_room()
{
    int i;

    set_short("The village pasture");
    add_item("pasture",
        "This communal pasture is used by all the villagers of this "+
        "village. Here the village' sheep and lambs graze and "+
        "grown their silky wool. Usually a young boy from the "+
        "village takes care of the flock.\n");

    add_item("ground",
        "The ground is covered with very short grass. The blade's ends "+
        "are marked with the sharp teeth of sheep. Here and there, "+
        "peeking out from the grass, some wildflowers have survived "+
        "the attention of the ever hungry sheep.\n");

    add_item("wildflowers",
        "Red, yellow and white wildflowers are scattered all "+
        "over the pastures, where the sheep eat it at its leisure.\n");

    add_item("grass",
        "Is green and lush.\n");

    add_item("view",
        "The view from here is magnificent! High mountains shroud with "+
        "mist and low clouds rise to the north. The dark and forbidden "+
        "bulk of the lord's castle, stand lonely to the northwest. The "+
        "black building strongly contrasts with the blue, clean sky. "+
        "A blue-green range of mountains with snowy-white ice caps "+
        "in their top run along to the south rushing down to the sea. "+
        "In between some of the mountain, the tantalizing sight of "+
        "sea adds a dash of aquamarine color to the wondrous view.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FIELD);

    set_up_herbs(this_object()->select_herb_files(({
	HERB_DIR + "meadowsweet.c",
	HERB_DIR + "primrose.c",
	HERB_DIR + "red_yarrow.c",
	HERB_DIR + "selfheal.c",
	HERB_DIR + "borage.c",
	HERB_DIR + "bee_balm.c",
	GONDOR_HERBS + "carrot_wild.c",
	GONDOR_HERBS + "fennel.c",
	GONDOR_HERBS + "mint.c",
	GONDOR_HERBS + "marjoram.c",
	GONDOR_HERBS + "strawberry.c",
	GONDOR_HERBS + "rosemary.c" })),
        ({"here", "ground"}), 3);

    set_tell_time(100);
    for(i = 0; i < 4; i++)
    {
        add_tell(({
	    "baah! baah!\n",
	    "be-eh! be-eh!\n",
	    "bla-ah! bla-ah!\n",
	    "A gust of wind caresses you with a smell of smoked wood.\n",
	    "A soft breeze from the forest caresses you with a spring-like " +
                "scent.\n",
	    "A eagle cries high in the sky.\n",
	    "A lamb bumps at your leg and jump away from you.\n",
	    "A falcon shrieks high in the sky.\n"})[random(8)]);
    }

    create_emerald_pasture();
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

