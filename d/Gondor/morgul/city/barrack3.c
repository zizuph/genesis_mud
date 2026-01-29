#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define NPC_FILES ({ MORGUL_DIR + "npc/ithil_man", \
                     MORGUL_DIR + "npc/variag",    \
                     MORGUL_DIR + "npc/mercenary", })

public void    reset_room();
static object *humans = allocate(6 + random(3));

public void
create_morgul_room()
{
    set_extraline("From the furniture here, you conclude that these are the " +
    "quarters of humans serving in the Morgul army. Stairs are leading up " +
    "to the first floor of the house. A door is leading out onto the street " +
    "to the east. All the windows are all closed with shutters.");
  add_item(({"stairs","stair"}), BSN(
    "Stairs are leading up to the first floor of the building. They are made " +
    "from stone slabs, and some of the steps have obviously been replaced recently. "));
  add_item(({"step", "steps"}), BSN(
    "The original steps are made from finely polished stone slabs, which " +
    "probably were hewn from a quarry in the Ephel Duath. The steps which " +
    "were used to repair the stairs look suspiciously like the roughly hewn " +
    "stones from the Morgul Road. Obviously, whoever repaired the stairs did not " +
    "go far to find replacements for the old steps. "));
  add_item(({"furniture"}), BSN(
    "There are beds along the south and west wall, and in the middle of the " +
    "room a wooden table stands, surrounded by several chairs. "));
  add_item(({"beds","cots","bed","cot"}), BSN(
    "These are very simple cots. A wooden frame around old sacks filled with " +
    "hay and straw, covered with rough blankets. Better than sleeping on the " +
    "cold stone floor, but not much. You count eight beds, four along the south " +
    "wall, four along the west wall. "));
  add_item(({"table"}), BSN(
    "A large wooden table is standing in the middle of the room. The table top " +
    "has been rudely treated with knives and other heavy and sharp objects and is " +
    "covered with deep scratches. "));
  add_item(({"chair", "chairs"}), BSN(
    "Around the table you can see almost a dozen " +
    "crude chairs, which certainly were not crafted by a master artisan. " +
    "Probably some bored soldier was tired of sitting on the floor and made them " +
    "from spare timber. At least they look to be sturdy. "));
  add_item(({"window","windows","shutters"}), BSN(
    "All windows have been closed with shutters. When you look closer you realise " +
    "that the shutters have been nailed to the walls from the outside, so you " +
    "cannot open them. "));
  set_road(5);
  set_side("north");

  clone_object(MORGUL_DIR+"city/doors/b3doorin")->move(TO);

  add_exit(MORGUL_DIR + "city/rooms/b3up","up","@@stairs",1);

  reset_room();
}

public void
clone_humans(object *npcs, float delay)
{
    int     n = sizeof(npcs),
            i;
    string  npc_file = ONE_OF_LIST(NPC_FILES);

    for (i = 0; i < n; i++)
    {
        if (!objectp(npcs[i]))
        {
            npcs[i] = clone_npc(npcs[i], npc_file);
            npcs[i]->add_act("close door");
            npcs[i]->add_cact("close door");
            set_alarm(delay / 2.0 + rnd() * delay, 0.0,
                &clone_humans(npcs, delay));
            break;
        }
    }
}

public void
reset_room()
{
    set_alarm(20.0 + rnd() * 20.0, 0.0, &clone_humans(humans, 60.0));
}

