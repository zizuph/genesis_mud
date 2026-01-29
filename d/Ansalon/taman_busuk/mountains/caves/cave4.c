#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>

inherit CAVE_BASE;

void
create_cave_room()
{
    set_short("a cave under the Taman Busuk mountains");
    set_long("You are standing in a narrow cave under the Taman " +
    "Busuk mountains. The uneven floor makes walking treacherous, " +
    "and the soft dripping of water gives the cave an eerie " +
    "atmosphere.\n");

    add_cave_items();

    add_item(({"floor", "uneven floor"}),
    "The uneven floor makes walking treacherous. Rocks are scattered " +
    "throughout, and there is no cleared path that you can see.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(CAVE_DIR + "cave2", "southwest");
    add_exit(CAVE_DIR + "cave5", "east");

    set_tell_time(70);
    add_tell("You hear the sound of running water coming from the east.\n");
    add_tell("A drop of cold water falls down your neck. Brrrrr.\n");
    add_tell("The telltale sounds of running water comes to you from " +
    "the east.\n");
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   if(interactive(ob))
      start_room_tells();
}

