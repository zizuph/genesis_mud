#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void    reset_room();

static object *wguard = allocate(6 + random(6));

public void
create_morgul_room()
{
    set_extraline("This is the southern part of the great Mordor Gate. " +
    "Looking to the east, you can see how the city was built to " +
    "block the exits of Mordor. The city wall fills the space between " +
    "steep cliffs to the south and the deep vale of the Morgulduin to " +
    "the north. Looking down into the city to the west " +
    "you see the great tower of Minas Morgul dominating the view. There " +
    "is a flight of stairs here leading down into the streets of the city."); 
    set_road(1);
    set_side("east");

    add_tower();
    add_view_east();
    add_stairs_down();

    add_exit(MORGUL_DIR + "city/wall/wall07","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/wall/wall09","south","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/barrstr2","down","@@block_npc",2);

    reset_room();
}

public object
clone_npc(object npc, string npc_file)
{
    int     rs = random(50);

    if (objectp(npc))
        return npc;

    npc = clone_object(npc_file);
    npc->set_restrain_path(MORGUL_DIR + "city/wall/");
    npc->set_random_move(5);
    npc->default_config_npc(40 + rs);
    npc->set_base_stat(SS_INT, 25 + random(15));
    npc->set_base_stat(SS_WIS, 25 + random(15));
    npc->set_base_stat(SS_DIS, 55 + rs);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

public void
reset_room()
{
    set_alarm(10.0 + rnd() * 20.0, 0.0, &clone_npcs(wguard, MORGUL_DIR + "npc/ithil_soldier", 120.0));
}

