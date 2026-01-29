/* File         : /d/Khalakhor/se_speir/rannoch/room/riverside_base.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02         
 * Purpose      : Base riverside file for the Loch Rannoch area.
 * Related Files: 
 * Comments     : Heavily modified/updated 01-03-19
 * Modifications: 
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
setup_riverside_herbs()
{
    herbs = HERBMASTER->query_herbs(({TERRAIN_DECIDUOUS,}));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"ground","underbrush","here"}),2);
}

int
climb_tree()
{
    write("You start to climb up a nearby tree, but you don't get "
        + "far before deciding that it's not worth the effort, and "
        + "climb down again.\n");

    say(QCTNAME(this_player())+ " climbs up a few feet in a nearby tree, "
                              + "then climbs down again.\n");

    TP->add_fatigue(-5);

    return 1;
}

void
create_add_items()
{

    add_item(({"river","rapid river","stream","water"}),
               "This river rushes in from the northern "
             + "mountains, and it seems to be in a great "
             + "hurry on its way south towards the sea. "
             + "It is only about twenty feet wide, but "
             + "you see no possibility of crossing it, "
             + "since it is not only rapid, deep, and "
             + "probably icy cold, but also too far down.\n");
    add_item(({"ground","floor","riverside","forest floor"}),
               "The ground is rough here, clearly a place "
             + "where few living beings go. Old roots and fallen "
             + "branches makes it hard to get anywhere.\n");
    add_item(({"ridge"}),
               "The ridge you stand on, as well as the one on "
             + "the other side of the river, has been created "
             + "by the river carving it's way through the "
             + "landscape. You doubt you would survive a dive "
             + "into the river from this height.\n");
    add_item(({"soil","loose soil","gravel","side","side of ridge",
               "side of the ridge"}),
               "The exposed side of the ridge is rather steep, and "
             + "with all the loose soil and gravel it looks "
             + "impossible to climb down safely.\n");
    add_item(({"trees","woods","forest"}),
               "The trees here lean out over the river on both "
             + "sides, making it hard for you to see the sky "
             + "through the foliage.\n");
    add_item(({"root","roots","old root","old roots",
               "branch","branches","fallen branch","fallen branches"}),
               "Old roots and branches that lie here, decaying.\n");
    add_item(({"other side","other side of the river","opposite side",
               "opposite side of the river"}),
               "The opposite side of the river looks just like this one, "
             + "a seemingly endless forest high above the river.\n");

    add_cmd_item(({"tree","up tree","rowan","up rowan","ash","up ash",
                   "birch","up birch","up"}),
                   "climb",
                    climb_tree);
    add_cmd_item(({"ridge","down","down ridge","down the ridge"}),
                   "climb",
                   "The side of the ridge looks very unsafe to climb "
                 + "down, consisting mostly of loose soil and gravel.\n");
    add_cmd_item(({"river","stream","rapid river"}),
                 ({"swim","enter","dive","jump"}),
                   "Diving from this height into the rapid, deep, "
                 + "and most likely icy cold river might not be such a "
                 + "good thing to do after all.\n");

}

void
create_room_tells()
{
   add_tell(({"You spot a large branch flowing by down on the river.\n",
              "You caught a glimpse of movement on the other side of "
            + "the river.\n",
              "A fierce wind sweeps in from the north, making the trees "
            + "rustle and lose a few leaves.\n",
              "A leaf falls gently to the ground.\n",}));
}

public void
create_loch_room()
{
    set_short("On a ridge above a rapid river");
    set_long("The forest ends here, where a very rapidly "
           + "flowing river cuts through the hills and woods flowing "
           + "southwards. You stand high above the river itself, and "
           + "on the other side the forest and hills continues on.\n");

    set_terrain(TERRAIN_MIXEDWOOD);

    create_add_items();

    set_tell_time(1000);
    create_room_tells();

    setup_riverside_herbs();
}
