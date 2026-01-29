/*
 * /d/Gondor/common/guild/gondor/armroom.c
 *
 * The armoury of the Gondorian rangers.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Prototypes:
void add_stuff();
public string read_plaque();

static object  jar, a_rack, w_rack, crate;

public void
create_room()
{
    set_short("the arms storage for the Rangers of Gondor");
    set_long(BS("This is a small room where the Rangers store weapons "
      + "and armours for later use. Racks line the walls, holding "
      + "weapons and armours separate and away from the floor. A "
      + "large plaque hangs on the wall just above the crates.\n"));
    
    add_item("plaque", read_plaque);
    add_cmd_item("plaque", "read", read_plaque);
    
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(RANGER_GON_DIR + "startchamber", "east", 0);

    add_stuff();
}

void
add_stuff()
{
    if (!objectp(crate))
    {
        crate = clone_object(RANGER_DIR + "obj/crate");
        crate->move(TO);
    }
    if (!objectp(a_rack))
    {
        a_rack = clone_object(RANGER_DIR + "obj/a_rack");
        a_rack->move(TO);
    }
    if (!objectp(w_rack))
    {
        w_rack = clone_object(RANGER_DIR + "obj/w_rack");
        w_rack->move(TO);
    }
    if (!objectp(jar))
    {
        jar = clone_object(RANGER_DIR + "obj/herbjar");
        jar->add_prop(OBJ_M_NO_GET, "The jar seems to have been glued to the floor!\n");
        jar->move(TO);
    }
}

public string
read_plaque()
{
   write(read_file("/d/Gondor/common/guild/txt/rog_plaque.txt"));
   return "";
}


