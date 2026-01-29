/*
 * Inside tent in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"
#include <language.h>
inherit TENT_BASE;
#define BREE_DIR            "/d/Shire/common/bree/"
inherit CAMP_DIR + "bree_orcs";
#define TO this_object()

object leader, *orcs = ({ });

//void make_orcs();

void
create_tent_room()
{
    add_my_desc("Unlike the other tents, this one is spacious " +
        "and relatively clean. Crudely constructed furniture is " +
        "in the tent along with a large bed.\n");

    add_exit(CAMP_DIR + "path01", "out");
    reset_shire_room();

    kingbed();
    furniture();
    chairs();
    table();
    reset_shire_room();
//    add_npc(BREE_DIR + "npc/chief_orc");
    add_npc(CAMP_DIR + "bree_orcs", random(5));
}


void reset_shire_room()
{

    setuid();
    seteuid(getuid());

  if(!leader)
    {
        leader = clone_object(BREE_DIR + "npc/chief_orc");
        leader->move(TO);
    }

    clone_tent_orcs();

}
