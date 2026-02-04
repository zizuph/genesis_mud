#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "A large boulder to your southwest " +
        "blocks passage in that direction.\n");
    add_item(("boulder"), "A large chunk of solid rock " +
        "with small flecks of some kind of ore embedded within.\n");

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_c5","west",0);
    add_exit(HILLS_PATH + "hills_c7","east",0);
    add_exit(HILLS_PATH + "hills_d6","north",0);
    add_exit(HILLS_PATH + "hills_b6","south",0);
    add_exit(HILLS_PATH + "hills_d7","northeast",0);
    add_exit(HILLS_PATH + "hills_d5","northwest",0);

    reset_room();

}
