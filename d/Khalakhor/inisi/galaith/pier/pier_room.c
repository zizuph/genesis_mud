/**********************************************************************
 * - Pier base room                                                 - *
 * - Created by Damaris 09/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types

#include "../defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/std/room";
inherit LIBPIER;

void
create_pier()
{
}

nomask void
create_khalakhor_room()
{
    set_short("A secluded pier");
    set_long("   This secluded pier is on the isle of Galaith. The "+
      "pier stretches from the south of the isle toward the water. "+
      "It is secluded and without much activity except for a few sea "+
      "gulls and a splash or two from creatures swimming in the waters. "+
      "The isle of Galaith rests to the north and from here you can "+
      "see large amounts of vegetation flourishing.\n");
    add_item(({"galaith isle", "isle"}),
      "The isle of Galaith is to the north. It is flourishing in vegetation. "+
      "There is also a large tower that rises majestically toward the sky.\n");
    add_item(({"vegetation"}),
      "There is a large amount of vegetation growing and flourishing "+
      "on the isle.\n");
    add_item(({"pier", "wooden pier"}),
      "The impressive pier is in extremely good shape and surprisingly "+
      "is quite secluded and deserted.\n");
    add_item(({"sky"}),
      "The sky is partly cloudy, and is more grey than blue.\n");
    add_item("dock","@@query_long");
    add_item(({"waters", "local waters", "water"}),
      "The local waters are a deep crystal blue.\n");
    add_item(({"land"}),
      "It is the lands of Khalakhor, and more precisely, the isle of "+
      "Galaith.\n");
    add_item(({"moorings"}),
      "These wooden posts support the pier, having been embedded deep "+
      "in the depths of the water, and stabilized by boulders.\n");
    add_item(({"posts", "wooden posts"}),
      "The wooden posts support the pier, preventing it from falling "+
      "into the harbor.\n");
    add_item(({"post", "wooden post"}),
      "Each wooden post differs only in location, and the number of "+
      "barnacles covering it.\n");
    add_item(({"boulders"}),
      "They are too deep under the water to be seen.\n");
    add_item(({"shore"}),
      "The shore is rocky, making movement and direct landing on the "+
      "shore impossible.\n");
    add_item(({"waves"}),
      "The waves are crash around violently at times along the harbor, "+
      "and would only be dangerous to those who cannot swim.\n");
    add_item(({"barnacles"}),
      "The barnacles cover the moorings, layer upon layer.\n");
    add_cmd_item("barnacles",({"get","take"}),"They are just out of " +
      "reach!\n");
       
    create_pier();
    reset_room();
}

    /* This is for smells in the room. */
void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with the sweet scent of the sea.\n");
         return;
     }
       
 }
