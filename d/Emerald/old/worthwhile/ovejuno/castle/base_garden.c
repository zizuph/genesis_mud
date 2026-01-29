
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

#include "../defs.h"

inherit HS;

#include <stdproperties.h>

#include "/d/Emerald/sys/terrain_types.h"
#include "/d/Emerald/sys/properties.h"

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
        "leaves resembling teeth and yellow flowers.\n");

    add_item(({"ground", "path"}),
        "The path is covered with green grass that has "+
        "overgrown outside the path bounderies. Here and there you, "+
        "see, peeking out from the grass, yellow flowers and other more "+
        "exotic flora.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);

    set_up_herbs(this_object()->select_herb_files(({
	HERB_DIR + "milky_rose.c",
	HERB_DIR + "scarlet_rose.c",
	HERB_DIR + "ebony_rose.c",
	HERB_DIR + "grave_fl.c",
	HERB_DIR + "borage.c",
	HERB_DIR + "marsh_mallow.c",
	HERB_DIR + "primrose.c",
	HERB_DIR + "selfheal.c",
	GONDOR_HERBS + "bean_fava.c",
	GONDOR_HERBS + "bean_green.c",
	GONDOR_HERBS + "blackberry.c",
	GONDOR_HERBS + "chervil.c",
	GONDOR_HERBS + "garlic.c",
	GONDOR_HERBS + "laurel.c",
        KRYNN_HERBS  + "dandelion.c", })),
        ({ "ground", "here", "bushes", "trees"}), 3);

    set_tell_time(100);
    for(i = 0; i < 4; i++)
    {
        add_tell(({
	    "You hear the chittering of insects somewhere in the garden.\n",
	    "The wind carries the aroma of roses.\n",
	    "The wind carries the sweet aroma of orchids.\n",
	    "You hear the water singing in the fountain.\n",
	    "You hear the sweet chirping of a sparrow.\n",
	    "A black and orange buttlefly hovers over your head and " +
                "flies away.\n",
	    "The winds carries the pungent aroma of rotten flowers and " +
	      "fruits.\n", })[random(7)]);
    }

    create_emerald_garden();
}

void
add_roses()
{
    add_item(({"plants", "roses"}),
        "You see roses of different shades and sizes. They are "+
        "white like snow, red like blood and black like midnight. "+
        "During the years of abandonment they have grown "+
        "uncontrollably. They are as tall as the hedge and cover "+
        "the left corner of the garden completely. You can't walk "+
        "through there. They are so intermigled that you don't "+
        "know where one bush starts and where another end. The "+
        "different aromas create a heady perfume that makes you "+
        "feel dizzy.\n");

    add_item("white roses",
        "These roses are like small hand fists, milky white "+
        "and with a sweet and subtle aroma of honey and milk.\n");

    add_item("red roses",
        "These roses are huge! They are as big as a bear paw. "+
        "Their aroma is intoxicating like a mature red wine. "+
        "The petals are dark red and remind you of dry blood.\n");

    add_item("black roses",
        "These roses are half the size of the red ones. They "+
        "smell like rotten meat. Their aroma makes you sick. "+
        "The petals are black like soot, midnight without "+
        "stars.\n");                                                         
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
