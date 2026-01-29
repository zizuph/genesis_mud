/*
 * Valley south of the Barrows
 * In the old downs, this use to be down4 and connects to 
 * the old downs quest/spell.
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "local.h"

inherit ROAD_BASE;

#define QUEST_BARROW  "/d/Gondor/common/quest/nv/edown"

void
create_road_room()
{
    set_areadesc("valley");
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("The valley stretches " +
        "both east and west between the hills and downs. Oak trees " +
        "line the west edge of the valley, blocking travel there. " +
        "Dense fogs obscure your vision.");


    add_exit("/d/Gondor/common/quest/nv/edown", "east",  "@@make_noise");
    add_exit(BAR_DIR + "bar11_out", "west");
    add_exit(DOWNS_DIR + "valley2", "south");

}



void make_noise() {
    write("You stumble around, trying to find a way out of the " +
        "dense fog.\n");
}

int quest_test()
{
    QUEST_BARROW->tele_tull_ball_just_to_load_the_room();
    if (QUEST_BARROW->quester_present()) make_noise();
    else
    {
        this_player()->catch_msg("You stumble off through the fog, " +
            "and find a place where it gets less dense.\n");
        this_player()->move_living("into the fog",QUEST_BARROW,1,0);
        return 1;
    }
  return 0;
}
