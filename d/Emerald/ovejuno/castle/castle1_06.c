
/* Castle_room06-The Audience Room.
 * Coded by Marisol (09/04/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"
inherit CASTLE_OV;

void
create_castle_room()
{

    set_short("The Audience room");
    set_long("As you enter this room, you see Lord Maldabroot sitting "+
        "in his throne-like sit, waiting for the next querent. Two "+
        "elven guards stand in attention side by side the throne-like "+
        "sit of their lord. The room here is wide and many burning "+
        "braziers are scattered around the room warming it and adding "+
        "light to the torches. One big stained-glass window is set in "+
        "the back wall where the elven lord is sitting. Statuary adorn "+
        "the corners of the room together with the ever present "+
        "tapestries and paintings. Group of elves are spread in the "+
        "room chatting in low voices. Maybe you can ask for an "+
        "audience.\n");

    add_item(({"elven guards", "guards"}),
        "These guards look alert to their environment. They look "+
        "quite strong too.\n");

    add_item("braziers",
        "Tall tripods hold metal bowls full of burning coals.\n");

    add_item("statuary",
        "Ethereal statues of elven noblemen and lovely elvenmaids "+
        "posing for eternity.\n");    


    add_rugs("They are of a rich royal blue, giving a stately look to " +
        "this room.");

    add_item("elves",
        "Elven courtiers huddle together in whispered talk.\n");

    add_item(({"stained-glass window", "window"}),
        "This window is the same style as the ones in the foyer. "+
        "The animal represented in this one is a majestic sphinx. A "+
        "royal-looking humanoid head gazes indifferently to the "+
        "waiting crowd, while his lioned body rests in a green field. "+
        "The humanoid features are elven from the slanted eyes to "+
        "its pointing ears. It seems so real that you would expect to "+
        "it to ask a riddle in any moment.\n");

    add_exit("castle1_02", "east");
}                                                                  
