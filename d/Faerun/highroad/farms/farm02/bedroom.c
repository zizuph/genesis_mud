/*
 * Kitchen of the farmhouse in Anduin
 * By Finwe, November 2005
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

#define VAMPIRES_OBJ_DIR  "/d/Faerun/guilds/vampires/obj/"
 
inherit BASE_FARMHOUSE;

object ob;

void
create_house_room()
{
    set_short("A large bedroom");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_long("This large bedroom is comfy looking. A "
    +"large bed sits against one wall and a small "
    +"bed against another. A painting hangs on the wall "
    +"above the large bed. There is a wardrobe in a "
    +"corner and windows are set in the walls. Beneath "
    +"a window is a dresser. Hanging from the ceiling "
    +"are large lamps, casting a warm glow. A large "
    +"rug covers the floor.\n");

    reset_room();

    add_exit(FARM2_DIR + "kitchen", "east");
    set_add_bedroom();
    set_add_rug("rectangular");
    set_extra_window("");
    set_extra_floor("A rectangular rug covers the floor.");
    set_large_bed();
    set_add_kids_bed();
    
    room_add_object(VAMPIRES_OBJ_DIR  + "vamp_painting2");
    
}


void
reset_room()
{
    ::reset_room();

    if(!present("_farm_human"))
    {
        ob = clone_object(FNPC_DIR + "fruit_npc");
        ob->set_monster_home(FARM2_DIR + "bedroom");
        ob->move(this_object());
    }
}
