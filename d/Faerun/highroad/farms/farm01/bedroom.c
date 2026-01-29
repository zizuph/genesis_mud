/*
 * Kitchen of the farmhouse in Anduin
 * By Finwe, November 2005
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARMHOUSE;

object ob;

void
create_house_room()
{
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("A comfortable bedroom");
    set_long("This large bedroom is comfortable looking. A large bed sits " +
        "against one wall and a small bed against another. A large rug " +
        "covers most of the floor. There are windows set in the walls. " +
        "Beneath a window is a dresser. In a corner of the room is a " +
        "wardrobe. Lamps hang from the ceiling casting a warm glow to " +
        "the room.\n");

    reset_room();

    add_exit(FARM1_DIR + "great", "west");
    set_add_bedroom();
    set_add_rug("rectangular");
    set_extra_window("");
    set_extra_floor("A rectangular rug covers the floor.");
    set_large_bed();
    set_add_kids_bed();

    num_of_windows = 3;

}


void
reset_room()
{
    ::reset_room();

    setuid();
    seteuid(getuid());

    if ((ob))
    {
        return;
    }
     ob = clone_object(FNPC_DIR + "girl");
     ob->set_monster_home(FARM1_DIR + "bedroom");
     ob->set_random_move(8);
     ob->set_restrain_path(FARM1_DIR);
     ob->move(this_object());
}
