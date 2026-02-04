#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "A large boulder to your northwest " +
        "blocks passage in that direction.\n");
    add_item(("boulder"), "A large chunk of solid rock " +
        "with small flecks of some kind of ore embedded within.\n");

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_b5","west",0);
    add_exit(HILLS_PATH + "hills_c6","north",0);
    add_exit(HILLS_PATH + "hills_c7","northeast",0);

    reset_room();
}

