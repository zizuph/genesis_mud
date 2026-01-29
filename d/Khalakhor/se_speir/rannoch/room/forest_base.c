/* File         : /d/Khalakhor/se_speir/rannoch/room/forest_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-21         
 * Purpose      : Base forest file for the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Heavily modified/updated 01-03-18/19
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
setup_forest_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_DECIDUOUS,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"ground","underbrush","heather","here"}),2);
}

int
climb_tree()
{
    write("You start to climb up a nearby tree, but you don't get "
        + "far before deciding that it's not worth the effort, and "
        + "climb down again.\n");

    say(QCTNAME(this_player())+ " climbs up a few feet in a nearby tree, "
                              + "then climbs down again.\n");

    TP->add_fatigue(-3);

    return 1;
}

void
create_add_items()
{
    add_item(({"ground","floor","dirt","forest floor"}),
               "The ground is covered in small shrubs, rocks, "
             + "grass, and the ever present heather.\n");
    add_item(({"trees","woods","forest","woodland","woodlands"}),
               "The trees grow quite far apart, and they have "
             + "been standing here for ages. Birch is the most "
             + "common tree in these parts, but rowan and ash "
             + "can also be seen.\n");
    add_item(({"tree","birch","ash","rowan"}),
               "There are many trees here, none of them stands out "
             + "from the others.\n");
    add_item(({"leaf","leaves","foliage","treetop","treetops"}),
               "The foliage above is not so dense, and you can see "
             + "through it.\n");
    add_item(({"view","surroundings"}),
               "Nothing but forest in all directions.\n");
    add_item(({"heather","flowers"}),
               "These are small, hardy evergreen shrubs with small "
             + "leaves and spikes of tiny flowers in different "
             + "shades of pink and purple. They seem to cover every "
             + "inch of ground available, giving these parts a "
             + "cheerful atmosphere.\n");
    add_item(({"grass"}),
               "Ordinary green grass.\n");
    add_item(({"rock","rocks","stone","stones","boulder","boulders"}),
               "Scattered across the forest floor are rocks and stones of "
             + "different shapes and sizes.\n");
    add_item(({"shrub","shrubs","bush","bushes","group","groups"}),
               "The shrubs and bushes of these woodlands grow near "
             + "the tree trunks or in small groups of their own.\n");

    add_cmd_item(({"tree","up tree","rowan","up rowan","ash","up ash",
                   "birch","up birch"}),
                   "climb",
                    climb_tree);
}
void
create_room_tells()
{
   add_tell(({"A breeze sweeps up from the east, passes through "
            + "the trees, and gently dies away, leaving you refreshed.\n",
              "A gentle wind caresses you, before dying away to nothing.\n",
              "A leaf falls gently to the ground.\n",}));
}
public void
create_loch_room()
{
    set_short("Ancient woodlands");
    set_long("This is an ancient forest, and no path can be seen. " 
           + "The trees are very old and majestic, reaching far up " 
           + "above you. Heather grows practically everywhere in sight, "
           + "creating a sea of pink and green between the trees and "
           + "around the rocks and shrubs of the forest floor.\n");

    set_terrain(TERRAIN_MIXEDWOOD);

    create_add_items();

    set_tell_time(600);
    create_room_tells();

    setup_forest_herbs();
}
