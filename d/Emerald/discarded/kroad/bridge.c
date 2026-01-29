/*
 * bridge.c
 * Kahlen Road, Bridge across the channel.
 * by Alaron August 31, 1996
 * Added Vamp functionality January 25, 1997
 * Added noiseroom - 13th Feb 97
 */

#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>
#include "defs.h"

inherit "/std/room";
inherit "/d/Emerald/kroad/vamp/climbroom";
inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";

#define SPLASH_ROOM VAMP_KR_DIR + "fallroom"
#define GRIP_DIFFICULTY TASK_DIFFICULT

void
create_ov_road()
{
    set_short("Stone bridge");
    set_long("   You are standing on the middle of an enormous stone "+
             "bridge. The bridge's construction and design is breathtaking. "+
             "Made from a single slab of stone, it seems to almost drip "+
             "out of the north cliff face and flow like pouring liquid "+
             "across to the south cliff face. Decorated with swirling, long "+
             "and sweeping carved lines, you struggle to fight off the "+
             "vertigo. At "+
             "either of the cliff faces a dark, dirt road greets the "+
             "stone bridge, surrounded by forest and overgrown greenery. Far "+
             "below the sound of churning ocean water can be heard rushing "+
             "through the channel.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "cliff face", "north cliff face", "south cliff face",
                "face", "cliff faces"}),
             "The cliff faces rise majestically at an almost complete "+
             "vertical angle out of the channel below, their black and craggy "+
             "faces mixing with the deep blue of the ocean water below. "+
             "Each of the cliff faces supports a dark, dirt road which is "+
             "surrounded by forest and overgrown greenery.\n");

    add_item( ({"below", "far below", "ocean", "down", "channel",
                "water"}),
             "The water below churns and splashes rapidly against the "+
             "cliff sides as it rushes through the narrow channel between "+
             "the wide ocean on the east side and the inlet on the west "+
             "side.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
                "vegetation", "greenery", "overgrown greenery"}),
             "Either side of the bridge meets a dark road. The road "+
             "is surrounded on all sides by overgrown greenery, bushes, "+
             "and other vegetation. Back beyond the vegetation you can "+
             "see the beginnings of the edge of a forest.\n");

    add_item( ({"forest", "forest edge", "edge of a forest"}),
             "The forest edge is visible beyond the low greenery surrounding "+
             "the road. It is a thick, green forest which seems to press "+
             "in against the road on all sides, surrounding it.\n");

    add_item( ({"road", "dirt road", "dark dirt road", "packed dirt road"}),
             "The dark, packed dirt road on either side of the bridge "+
             "lead off into the forest and wood covering the edges of the "+
             "cliffs both to the north and south. The road looks very "+
             "well travelled. The moisture, puddles and mud on the road "+
             "are probably due to the sea spray causing moisture to "+
             "collect at this altitude.\n");
    
    add_exit(PATH + "eroad6", "north", 0, 1);
    add_exit(PATH + "eroad7", "south", 0, 1);
}

void search_object(string str)
{
    object *players, tp = this_player();
 
    write("While searching around the bridge, you hear a faint click "+
          "and suddenly find yourself falling through a hole!! \n\n");
    tp->move_living("M", VAMP_AREA_DIR + "ubridge", 1, 0);
    tell_room(VAMP_AREA_DIR + "ubridge",
               QCTNAME(tp)+" tumbles awkwardly down through the trap "+
                "door in the bridge above.\n", tp);

    if (climb_test(tp, TASK_DIFFICULT + 200))
    {
        write("You manage to grip hold of the rails to stop your " +
            "fall to the water far below!\n");
        tell_room(VAMP_AREA_DIR + "ubridge",
            QCTNAME(tp) + " manages to grip hold of the rails, " +
            "stopping " + tp->query_possessive() + 
            " fall to the water below.\n",tp);
    }
    else
    {
        write("You reach out to grip hold of the rails but slip, " +
              "falling far to the water below!!!\n\n");
        tell_room(VAMP_AREA_DIR + "ubridge",
                  QCTNAME(tp)+" reaches out to grip hold of the rails "+
                  "but slips, falling to the water below.\n", tp);

        fall_down(tp, ({ VAMP_AREA_DIR + "cliff1",
                         VAMP_AREA_DIR + "cliff2",
                         VAMP_AREA_DIR + "cliff3",
                         VAMP_AREA_DIR + "cliff4", }));
                         
        set_alarm(0.0, 0.0, &tp->move_living("M", 
            VAMP_AREA_DIR + "fallroom", 1, 0));
    }

    map(FILTER_PLAYERS(all_inventory(TO)),
        &->catch_msg("Almost too quick to notice, in the "+
        "corner of your eye you see "+ QTNAME(tp) +
        " slip down through a hole in the "+
        "bridge. The hole is gone before you "+
        "can react.\n"));
}



