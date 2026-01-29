/* File         : /d/Khalakhor/se_speir/rannoch/room/c_00.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";

int climb_tree();

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

    add_item(({"river","rapid river","stream","water"}),
               "This river rushes in from the northern "
             + "mountains, and it seems to be in a great "
             + "hurry on its way south towards the sea. "
             + "It is only about twenty feet wide, but "
             + "you see no possibility of crossing it, "
             + "since it is not only rapid, deep, and "
             + "probably icy cold, but also too far down. "
             + "There is a bridge across, but it has been "
             + "destroyed.\n");
    add_item(({"other side","other side of the river","opposite side",
               "opposite side of the river"}),
               "The opposite side of the river looks just like this one, "
             + "a seemingly endless forest high above the river. "
             + "You can see a narrow road winding its way into "
             + "the forest, from where the bridge once began.\n");
    add_item(({"bridge","collapsed bridge","destroyed bridge"}),
               "The bridge looks well-built, and would have withstood "
             + "almost anything nature had thrown against it. Surely "
             + "its ruination must be the work of a living being. It "
             + "is useless now, you can not use it to cross the river "
             + "here.\n");
    add_item(({"ground","floor","dirt","road"}),
               "The road you stand on has been well-used, at least to "
             + "the point in time when the bridge was demolished. Now "
             + "nature has begun its reclamation, and the ground is "
             + "no longer kept clear of leaves, grass and twigs.\n");
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
    add_item("ridge",
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


    add_cmd_item(({"tree","up tree","rowan","up rowan","ash","up ash",
                   "birch","up birch","up"}),
                   "climb",
                    climb_tree);
    add_cmd_item(({"ridge","down","down ridge","down the ridge"}),
                   "climb",
                   "The side of the ridge looks very unsafe to climb "
                 + "down, consisting mostly of loose soil and gravel.\n");
    add_cmd_item(({"bridge","the bridge","under bridge","under the bridge"}),
                 ({"crawl","climb"}),
                   "The bridge is hanging straight down from the opposite "
                 + "side of the river, there is not even a way of getting "
                 + "to it.\n");
    add_cmd_item(({"into forest","into the forest","into woods","into the woods"}),
                   "peer",
                   "You peer into the woods, your sight sweeping across the "
                 + "purple-green sea and the grey trees that grows among it. "
                 + "However, that is all you can see.\n");

   add_exit(ROOM + "b_00.c","north",0,3,1);
   add_exit(ROAD + "b_01.c","northeast",0,1,0);
   add_exit(ROOM + "c_01.c","east",0,3,1);
   add_exit(ROOM + "d_01.c","southeast",0,3,1);
   add_exit(ROOM + "d_00.c","south",0,3,1);

}

public void
create_khalakhor_room()
{

    set_short("End of the road");
    set_long("The road ends here, high above a fierce river. A bridge was "
           + "once built across it, but it has been destroyed and can not "
           + "be used to get to the other side. The road turns northeast, "
           + "into deeper woods.\n");

    add_tell(({"The planks that hang from the shattered remains of "
             + "the bridge groans and creaks in the wind.\n",
               "You spot a large branch flowing by down on the river.\n",
               "You caught a glimpse of movement on the other side of "
             + "the river.\n",
               "A fierce wind sweeps in from the north, making the trees "
             + "rustle and lose a few leaves.\n",
               "A leaf falls gently to the ground.\n",}));

    set_terrain(TERRAIN_RROAD);

    create_add_items();

    set_tell_time(900);
}

