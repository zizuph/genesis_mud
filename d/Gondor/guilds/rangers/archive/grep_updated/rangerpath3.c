/* /d/Gondor/anorien/druedain/rangerpath3.c
 * Modifications: April 24, 2004, Tigerlily, for ranger
 *   recode
 *
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#ifdef NEW_RANGERS_OPEN
#include "/d/Gondor/guilds/rangers/rangers.h"
#endif

#define OTHER_ROOM ("/d/Gondor/anorien/druedain/rangerpath2")

public int     enter_portal();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("old path");
    set_area("western");
    set_areaname("the Druedain Forest");
    set_land("Gondor");
    set_grass("soft, light green");
    set_treetype("large oaks");
    set_extraline("Large oak trees along with some birches make up most of the "+
        "forest here, their branches tangled above your head, almost forming "+
        "a roof. There seems to be a path running east and west among the trees "+
        "here, though nothing special is visible in those directions.");

    add_exit(ANO_DIR + "druedain/rangerfield", "west", enter_portal, 1, 1);
    add_exit(ANO_DIR + "druedain/rangerpath2", "east",            0, 1, 1);

    add_item("path","The path is difficult to see here. It seems to lead east and west,\n"+
        "but you find nothing to make you feel certain about that.\n");
    add_item(({"tunnel","branches"}),"The trees growing so tight together, and their branches tangled \n"+
        "into eachother above all makes it feel as if you're in a great green hall.\n");
    add_item(({"trees","birches","oak trees","oaks"}),
        "There are oaks and birches, growing quite close everywhere.\n"+
            "It creates a feeling of being inside a great hall.\n");
}

private void
do_exp_bit(object player)
{
    if (player->test_bit("Gondor",GONDOR_GROUP, RANGER_TEST_BIT))
        return;
    FIX_EUID
    write("At the same time you feel a little more experienced.\n");
    player->add_exp_quest(RANGER_TEST_EXP);
    player->set_bit(GONDOR_GROUP, RANGER_TEST_BIT);
    LOG_QUEST(player, RANGER_TEST_EXP, "RANGER TEST");
    return;
}

public int
enter_portal()
{
    FIX_EUID
    if ( (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT)) &&
            (query_friend_or_foe(TP->query_real_name()) > -1) )
    {
        write("You pass through the bushes, and follow a new path from \n"+
	      "here. After a while, you enter a clearing.\n");
        return 0;
    }
    if (objectp(present("Ranger_Test_Proof",TP)) &&
        !(OTHER_ROOM->query_trapped_today(TP->query_real_name())))
    {
        write("You pass through the bushes, and follow the path westwards,\n"+
	      "until you enter a clearing.\n");
        do_exp_bit(TP);
        return 0;
    }
    write("You pass through the bushes, and try to follow the path west.\n"+
	  "After some time, you enter a clearing of some kind.\n");
    TP->move_living("west",ANO_DIR+"druedain/forest1",1,0);

    return 1;
}

public int
hook_friend_or_foe(object pl)
{

#ifndef NEW_RANGERS_OPEN
    if ((R_OUTLAW)->query_outlaw(pl->query_real_name()))
        return -1;
#endif

#ifdef NEW_RANGERS_OPEN
    if ((MANAGER)->query_is_outlaw(pl->query_real_name()))
        return -1;
#endif
    return 0;
}


