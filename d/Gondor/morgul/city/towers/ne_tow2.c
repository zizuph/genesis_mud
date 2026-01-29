#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

/* April 2002: Cleaned up BSN, line run-overs, typos. Serif. */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *wguard = allocate(3 + random(3));

public void
create_morgul_room()
{
   set_extraline("All around you are walls made from dark roughly hewn "
       + "boulders. On the northern wall of the room, a flight of stairs "
       + "is leading up to the top and down into the ground floor. " 
       + "A doorway to the southwest is leading out onto the top of "
       + "the city walls.");
   set_road(9);
   set_short_desc("inside the northeast tower of Minas Morgul");
   set_side("northeast");

   add_item(({"ceiling","roof"}), ("The ceiling seems to be made of the "
       + "same dark boulders as the walls, only they have been hewn into "
       + "long slabs and then polished.\n"));
   add_item(({"floor","ground"}), ("The floor is made out of roughly cut "
       + "wooden planks.\n"));
   add_item(({"flight","stair","stairs","flight of stairs"}), ("Along the "
       + "northern wall of the room, a flight of stairs is leading up and "
       + "down into the next levels of the building. The steps of the "
       + "stairs are made of the same large stone slabs as the floor.\n"));

   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_I_INSIDE,1);
   add_exit(MORGUL_DIR + "city/wall/wall04","southwest","@@check_exit",1);
   add_exit(MORGUL_DIR + "city/towers/ne_tow1","up",
       "@@tower_stairs|uptop@@",4);
   add_exit(MORGUL_DIR + "city/towers/ne_tow3","down",
       "@@tower_stairs|down@@",3);

   reset_room();
}

public object
clone_npc(object npc, string npc_file)
{
    int     rs = random(51);

    if (objectp(npc))
        return npc;

    npc = ::clone_npc(npc, npc_file);

    npc->set_restrain_path(MORGUL_DIR + "city/towers/");
    npc->set_random_move(5);
    npc->default_config_npc(50 + rs);
    npc->set_base_stat(SS_INT, 25 + random(22));
    npc->set_base_stat(SS_WIS, 25 + random(25));
    npc->set_base_stat(SS_DIS, 45 + rs);

    return npc;
}

public void
reset_room()
{
    set_alarm(30.0 + rnd() * 60.0, 0.0,
        &clone_npcs(wguard, MORGUL_DIR + "npc/ithil_soldier", 60.0));
}

