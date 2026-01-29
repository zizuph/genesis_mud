#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *orcs = allocate(3 + random(2));

public void
create_morgul_room()
{
    set_extraline("These seem to be the living quarters of uruk officers " +
    "in the Morgul army. It is dirty like downstairs, but the furniture " +
    "is in better repair. Unlike downstairs, the windows here have not " +
    "been nailed shut with boards. A flight of stairs is leading down " +
    "to the ground floor.");
  add_item(({"stairs","stair","flight","flight of stairs"}), BSN(
    "A broad flight of stairs is leading down to the ground floor of the " +
    "building. The stairs are made of black stones, which once probably " +
    "were beautifully polished, but now they are dirty and dull. "));
  add_item(({"chair","chairs","cot","cots","bed","beds","furniture"}), BSN(
    "There are several beds, each with a wooden chair. The beds are simple " +
    "cots filled with rags and straw. Impressing luxury for orcs, but " +
    "members of other races probably would not appreciate it. "));
  add_item(({"street","window","windows"}), "@@exa_window|"+
    "Through the window you can look out onto the dark and narrow " +
    "Barracks Street which runs from north to south at the foot of the city wall " +
    "just outside the building. |" +
    MORGUL_DIR+"city/barrstr4@@");
  set_road(5);
  set_side("east");
  add_prop(ROOM_I_LIGHT,1);

    add_exit(MORGUL_DIR + "city/barrack7","down",
        "@@stairs|down the flight of stairs leading to the ground floor@@",1);

  reset_room();
}

public void
reset_room()
{
    set_alarm(30.0 + rnd() * 60.0, 0.0,
        &clone_npcs(orcs, MORGUL_DIR + "npc/ithil_uruk", 60.0));
}


