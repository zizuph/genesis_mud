/*
 * Shore of river Bruinen
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit SHORE_BASE;
#define MAX_TROLLS 3

static object *trolls = allocate(MAX_TROLLS);

void
create_shore_room()
{
    set_vbfc_extra(shore_desc);

    add_exit(RIVER_DIR +   "shore04", "north",0,4);
    add_exit(RIVER_DIR +   "shore02", "south",0,4);
    add_exit(TROLLSH_DIR + "mpath2",  "west",0,4);
    reset_shire_room();
}


void
reset_shire_room()
{

    int index;

    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());

    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_TROLLS; index++)
    {
        if (!objectp(trolls[index]))
        {
            trolls[index] = clone_object(TROLLSH_DIR+ "npc/trollet");
            trolls[index]->set_restrain_path(({
                RIVER_DIR,
                TROLLSH_DIR}));
            trolls[index]->set_random_move(3);
            trolls[index]->set_monster_home(RIVER_DIR + "shore03");
            trolls[index]->move(TO);

        }
    }
}
