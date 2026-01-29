#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Orphan;

public void
create_gondor()
{
    set_short("a room in an orphanage");
    set_long(BSN("This room of the orphanage is even dirtier than the "
      + "one to the west, but the dirt here is from paint and chalk."));
    add_item(({"paint", "chalk", }), BSN(
        "The walls and the floor are covered by spots of paint and "
      + "chalk in many colours."));
    add_item(({"wall", "walls", "floor", }), BSN(
        "The walls and the floor are covered by spots of paint and chalk "
      + "in many colours. On the north wall, among all the spots, there "
      + "is a picture painted onto the wall."));
    add_item(({"north wall", "picture", "painting", "mural", }), BSN(
        "The painting on the north wall is of an impressive strength and "
      + "power. It shows what could be a dream for all orphans living "
      + "here: A pastoral scene at the edge of a village between a "
      + "forest and wide green fields with children playing on the "
      + "fields and in the village."));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PELAR_DIR + "homes/orphanage","west",0);

    reset_room();
}

public void
reset_room()
{
    Orphan = clone_npc(Orphan, PELAR_DIR + "npc/painter");
}

