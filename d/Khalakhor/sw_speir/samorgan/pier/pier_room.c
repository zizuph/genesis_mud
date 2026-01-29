/* Pier base room
 * In SaMorgan
 * Created by Damaris 07/Y2K
 */
#pragma save_binary
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/std/room";
inherit LIBPIER;

public void
create_pier()
{
}

public void
reset_pier()
{
}

public int *
query_global_coords()
{
    return ({0, 0});
}

public void
reset_room()
{
    reset_pier();
}

public void
create_khalakhor_room()
{   set_short("A pier in SaMorgan");
    set_long("   This is a wooden pier in SaMorgan. SaMorgan beach rises "+
      "toward the north, which settles along the southwestern speir of "+
      "Khalakhor. The dock itself extends out into a small harbor. The "+
      "harbor doesn't afford much protection from storms that pass here "+
      "from the open sea. Departing ships sail into Miath Rae. Miath Rae "+
      "becomes Cuan Siorruidh, the ocean surrounding Khalakhor.\n");
    add_item(({"samorgan", "village"}),
      "SaMorgan is a small fishing village that rests along the "+
      "southwestern speir of Khalakhor.\n");
    add_item(({"beach", "beaches", "sand"}),
      "A light coloured beach rises toward the northern most part of "+
      "the pier.\n");
    add_item(({"southwest speir", "present speir", "southwestern speir"}),
      "The southwestern speir of Khalakhor is where you are at the moment.\n");
    add_item(({"southeast speir", "distant speir", "southeastern speir"}),
      "You are unable to see it from here.\n");
    add_item(({"speir","speirs"}),
      "Which one?\n");
    add_item(({"pier","wooden pier"}),
      "The wooden pier is in excellent condition. The citizens of SaMorgan "+
      "take pride in taking care of them, which is needed since there "+
      "are frequent storms here.\n");
    add_item(({"sky"}),
      "The sky is partly cloudy, and is more grey than blue.\n");
    add_item("dock","@@query_long");
    add_item(({"harbor"}),
      "This harbor is no way near enclosed by land, so any buffering "+
      "effects of a storm that land could give is lost here in these "+
      "local waters.\n");
    add_item(({"waters", "local waters", "water"}),
      "The local waters are a deep crystal blue.\n");
    add_item(({"land"}),
      "It is the land of Khalakhor, and more precisely, the southwestern "+
      "speir of the continent.\n");
    add_item(({"sea","miath rae"}),"Past the harbour, the deep blue " +
      "waters of Miath Rae can be seen.\n");
    add_item(({"ocean","cuan siorruidh"}),
      "Far in the distance, the waters of Cuan Siorruidh can barely "+
      "be gleaned.\n");
    add_item(({"moorings"}),
      "These wooden posts support the pier, having been embedded deep "+
      "in the depths of the water, and stabilized by boulders.\n");
    add_item(({"posts", "wooden posts"}),
      "The wooden posts support the pier, preventing it from falling "+
      "into the harbour.\n");
    add_item(({"post", "wooden post"}),
      "Each wooden post differs only in location, and the number of "+
      "barnacles covering it.\n");
    add_item(({"boulders"}),
      "They are too deep under the water to be seen.\n");
    add_item(({"shore"}),
      "The shore is rocky, making movement and direct landing on "+
      "the shore impossible.\n");
    add_item(({"waves"}),
      "The waves are crash around violently at times along the harbor, "+
      "and would only be dangerous to those who cannot swim.\n");
    add_item(({"small rise","rise", "small beach rise"}),
      "The small beach rise protects SaMorgan from the high waves "+
      "of storms.\n");
    add_item(({"barnacles", "barnacle"}),
      "The barnacles cover the moorings, layer upon layer.\n");
    add_cmd_item("barnacles",({"get","take"}),"They are just out of " +
      "reach!\n");


    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PIER | TERRAIN_SALTWATER);

    create_pier();
    reset_room();
}
