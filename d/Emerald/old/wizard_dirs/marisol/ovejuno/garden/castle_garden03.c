

/*The Manor's Garden III
 * Coded by Marisol (7/31/97)
 * The bee npc and the weak sting poison is Gondor code.
 * Coded by Gnadnar. The rest is mine.
 * Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol (07/23/98) to be used in the village of
 * Ovejuno in Emerald.*/

#pragma strict_types

#include "defs.h"
inherit CASTLE_GARDEN;
 
void
create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. A great variety "+
        "of ornamental plants run wild in this forgotten place. "+
        "The only sounds that can be heard are from insects and "+
        "bird that seem to talk to each other in a secret "+
        "language. The breeze brings the sweet music of water "+
        "falling down a fountain. The smell of roses is strong here, "+
        "overwhelming your senses.\n");

    add_item("plants",
        "You see rosebushes of different shades and sizes. They are "+
        "white like snow, red like blood and black like midnight. "+
        "During the years of abandonment they have grown "+
        "uncontrollably. They are as tall as the hedge and cover "+
        "the right corner of the garden completely. You can't walk "+
        "through there. They are so intermigled that you don't "+
        "know where one bush start and where another end. The "+
        "different aromas create a heady perfume that makes you "+
        "feel dizzy.\n");

    add_item("white roses",
        "These roses are like small hand fists, milky white and "+
        "with a sweet and subtle aroma of honey and milk.\n");

    add_item("red roses",
        "These roses are huge! They are as big as a bear paw. "+
        "Their aroma is intoxicating like a mature red wine. "+
        "The petals are dark red and remind you of dry blood.\n");

    add_item("black roses",
        "These roses are half the size of the red ones. They "+
        "smell like rotten meat. Their aroma makes you sick. "+
        "The petals are black like soot, midnight without "+
        "stars.\n");                                                         


    add_exit("castle_garden05", "north");
    add_exit("castle_garden01", "west");

    reset_room();

}

void
reset_room()
{
    if(!present("g_bee"));
    {
     setuid();
     seteuid(getuid());
     clone_object(CASTLE_GARDEN_NPC + "g_bee")->move(this_object());
    }
}
