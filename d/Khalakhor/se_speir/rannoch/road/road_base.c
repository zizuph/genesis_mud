/* File         : /d/Khalakhor/se_speir/rannoch/road/road_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-21         
 * Purpose      : Base road file for the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Heavily modified/updated 01-03-19
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

int climb_tree();
string *herbs;

public void
setup_road_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_PLAIN,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), (({"here","ground"})), 2);
}


int
climb_tree()
{
    write("You start to climb up a nearby tree growing close to the road, "
        + "but you don't get far before deciding that it's not worth the "
        + "effort, and climb down again.\n");

    say(QCTNAME(this_player())+ " climbs up a few feet in a nearby tree "
                              + "close to the road, then climbs down again.\n");

    TP->add_fatigue(-5);

    return 1;
}

void
create_add_items()
{

    add_item(({"ground","floor","dirt","road"}),
               "The road you stand on is about ten feet wide, enough "
             + "for a cart or wagon to pass, although it looks like "
             + "it once was more used than it is today. There are "
             + "weeds and grass growing were once people trampled "
             + "the ground, and leaves and twigs fallen down from "
             + "the trees above. You doubt that there will even be "
             + "trace left of this road in fifty years or so.\n");
    add_item(({"twig","twigs","grass","leaves","leaves","weeds"}),
               "The twigs and leaves that have fallen down from above, "
             + "as well as the grass and weeds that now thrives here, "
             + "now covers over half of what you see used to be a "
             + "well-used road.\n");
    add_item(({"trees","woods","forest"}),
               "On either side of you grows tall, aged trees, and the "
             + "road twists and turns among them. The forest is vast, "
             + "but not uninviting.\n");
    add_item(({"tree","birch","ash","rowan"}),
               "There are many trees here, none of them stands out "
             + "from the others.\n");

    add_cmd_item(({"tree","up tree","rowan","up rowan","ash","up ash",
                   "birch","up birch","up"}),
                   "climb",
                    climb_tree);
    add_cmd_item(({"into forest","into the forest","into woods","into the woods"}),
                   "peer",
                   "You peer into the woods, your sight sweeping across the "
                 + "purple-green sea and the grey trees that grows among it. "
                 + "However, that is all you can see.\n");

}

void
create_room_tells()
{
   add_tell(({"The trees sway and groan when a sudden wind comes in "
            + "from the east, sweeps along the road, and fades away.\n",
              "You hear something moving in the woods behind you.\n",
              "A leaf falls gently to the ground.\n",
              "A gentle breeze rustles the foliage above, sending a "
            + "few leaves to the ground.\n",}));
}

public void
create_loch_room()
{

    set_short("On a small road");
    set_long("You are on a small road, winding its way through the "
           + "trees of the forest that loom above your head.\n");

    set_terrain(TERRAIN_RROAD);

    create_add_items();

    set_tell_time(550);
    create_room_tells();

    setup_road_herbs();
}
