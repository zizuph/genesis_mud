/* Navarre June 2006, changed the clone boots to clone_unique */


#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <money.h>
#include <stdproperties.h>
inherit "lib/unique";

inherit CAVE_BASE;

object reb1, chest, potion, potion2, money, boots;

#define POTION "/d/Ansalon/estwilde/obj/dwarf_potion"

void
reset_cave_room()
{
    if (!objectp(reb1))
      {
        reb1 = clone_npc(MNPC + "fallen_knight");

      }

    reb1->close_chest();

    if (!objectp(chest))
      {
        chest = clone_object(MOBJ + "chest");
        chest->move(TO);
      }

    if (!P(potion, chest))
      {
        potion = clone_object(POTION);
        potion->move(chest, 1);
        potion2 = clone_object(POTION);
        potion2->move(chest, 1);

      }

    if (!P(boots, chest))
      {
          boots = clone_unique(MOBJ + "boots", 4);
          boots->move(chest, 1);
      }

    if (!objectp(money))
      {
          money = MONEY_MAKE_GC(20);
          money->move(chest, 1);
      }

}

void
create_cave_room()
{
    set_short("within a large canvas tent");
    set_long("You stand within a large canvas tent that looks like it is " +
    "being used as both a command centre and the living quarters of this " +
    "band of freedom fighters.  In the middle of the tent is a heavy " +
    "wooden table covered in maps of the surroundings.\n");

    add_cave_items();
    add_camp_items();

    add_item(({"floor", "uneven floor"}),
    "The cave floor has been cleared of loose rocks and rubble.\n");

    add_item(({"heavy wooden table","wooden table","table"}),
    "This is a wooden table, crudely built. Scattered across it are " +
    "numerous maps of the surrounding region.\n");
    add_item(({"maps","map"}), "Scattered on the table are maps of the " +
    "surrounding area, showing the valley between Neraka and Sanction.\n");

    add_item(({"tent", "large tent"}),
    "A large tent made of canvas.\n");
    add_item(({"opening","opening of the tent"}),
    "The opening of the tent faces the north.\n");


    add_prop(ROOM_I_LIGHT, 4);

    add_exit(CAVE_DIR + "camp3", "north");

}

