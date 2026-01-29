#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *wguard = allocate(3 + random(3));

public void
create_morgul_room()
{
    set_extraline(
    "To the north, you can look down into the vale of the Morgulduin, " +
    "to the east you see the dark slopes of the Ephel Duath rising " +
    "towards the pass high above the city. A flight of stairs is " +
    "leading down into the tower.");
  set_road(9);
  set_short_desc("on top of the northeast tower of Minas Morgul");
  set_side("northeast");

  add_item(({"tower","northeast tower"}), BSN(
    "The top of the northeast tower is only a few metres above the top " +
    "of the city walls. But the tower has been built in front of the city " +
    "walls proper so from its top one has a clear view of the outer side " +
    "of the walls."));
  add_item(({"steps","stair","stairs","flight of stairs"}), BSN(
    "A flight of stairs leading down into the tower. "));
    add_view_east();
    add_view_north();
  add_exit(MORGUL_DIR + "city/towers/ne_tow2","down","@@tower_stairs|top@@",3);

    reset_room();
}

public object
clone_npc(object npc, string npc_file)
{
    int    rs = random(50);

    if (objectp(npc))
        return npc;

    npc = ::clone_npc(npc, npc_file);
    npc->set_restrain_path(MORGUL_DIR + "city/towers/");
    npc->set_random_move(5);

    return npc;
}

public void
reset_room()
{
    set_alarm(30.0 + rnd() * 60.0, 0.0,
        &clone_npcs(wguard, MORGUL_DIR + "npc/ithil_guard", 60.0));
}

