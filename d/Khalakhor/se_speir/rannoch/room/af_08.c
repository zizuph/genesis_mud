/* File         : /d/Khalakhor/se_speir/rannoch/room/af_08.c
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

int listen_water();

int
listen_water()
{
    write("You close your eyes for a while and listen to the "
        + "furious, but yet soothing roar of the waters below.\n");

    say(QCTNAME(this_player())+ " closes " + HIS + " eyes for a few "
                              + "seconds, as if listening to something.\n");

    return 1;
}

void
create_add_items()
{
   add_item(({"fall","falls","waterfall"}),
              "You have a rather good view of the waterfall from "
            + "up here. It is caused by the two rivers joining, "
            + "and at the same time crashing down the rocks and "
            + "boulders. It is not that violent due to its "
            + "wideness, but it is rather loud.\n");
   add_item(({"rivers","water"}),
              "The western river is very rapid, and has "
            + "run a long way from the mountains in the far north. "
            + "The southern river is relatively calm, coming from "
            + "a source unknown to you. Both look very deep "
            + "and cold, and diving into any of them would be dangerous.\n");
   add_item("river",
            "There are two rivers, one west of you, and one south of you.\n");
   add_item(({"western river","west river","rapid river"}),
              "This river flows down from the northern mountains in great "
            + "haste, and it looks quite deep. On its other side is a thin "
            + "strip of bare land, just below the forest plateau.\n");
   add_item(({"southern river","south river","gentle river"}),
              "The southern river immediately bends northeast, making it "
            + "impossible for you to see exactly which direction it is "
            + "coming from. It is wider than the western river, and "
            + "a lot more gentle in comparison.\n");
   add_item(({"strip","narrow strip","bare land"}),
              "It runs alongside the western river just on the other "
            + "side of it from where you stand.\n");   
   add_item(({"rocks","boulders"}),
              "The rocks you stand on are fairly large, ordinary boulders.\n");
   add_item(({"forest","woods","woodlands"}),
              "The forest grows on both sides on both rivers, as "
            + "well as north of here. You can not see far south, as "
            + "the treetops of the lower woodlands block your view.\n");
   add_item(({"tree","trees","birch","ash","rowan"}),
              "There are no trees growing here, but the forest is not far "
            + "off to the north.\n");
   add_item(({"leaf","leaves","foliage","treetop","treetops"}),
              "The foliage above is not so dense, and you can see "
            + "through it.\n");
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
   add_item(({"other side","other side of the river","opposite side",
              "opposite side of the river","plateau","forest plateau"}),
              "The opposite side of the west river looks just like this one, "
            + "a seemingly endless forest high above the river. The other "
            + "side of the south river is much lower, but still consists "
            + "of dense woods.\n");
   add_item(({"slope","rocky slope"}),
              "On the west side of the waterfall you spot the beginning "
            + "of a rocky slope running down alongside the waterfall.\n");
   
   add_cmd_item(({"tree","the tree","trees","up"}),
                  "climb",
                  "There are no trees here to climb.\n");
   add_cmd_item(({"river","rivers","water","water","waterfall",
                  "to the waterfall","to the water","to the river",
                  "to the rivers"}),
                  "listen",
                  listen_water);

   add_exit(ROOM + "ae_08.c","north",0,2,0);
   add_exit(ROOM + "ae_09.c","northeast",0,2,0);
}

void
create_room_tells()
{
   add_tell(({"A breeze sweeps up from the east, passes through "
            + "the trees, and gently dies away, leaving you refreshed.\n",
              "A gentle wind caresses you, before dying away to nothing.\n",
              "A leaf falls gently to the ground.\n",
              "You spot a large branch flowing by down on the west river.\n",
              "You caught a glimpse of movement on the other side of "
            + "the south river.\n",
              "A fierce wind sweeps in from the north, making the trees "
            + "rustle and lose a few leaves.\n",
              "The roar from the waterfall below becomes even louder for "
            + "a brief while.\n",
              "A strong wind almost made you lose your balance.\n",}));
}

public void
create_khalakhor_room()
{

    set_short("High above two rivers");
    set_long("You are at a place where no trees grow, and "
           + "the ground consists of rocks and boulders. "
           + "The view is fantastic, offering the sight of "
           + "two rivers joining just below you, and together "
           + "they crash down the rocky slope to the south, "
           + "creating a loud waterfall. There is forest all "
           + "around you.\n");

    set_terrain(TERRAIN_RWATERFALLS);

    create_add_items();

    set_tell_time(377);
    create_room_tells();
}

