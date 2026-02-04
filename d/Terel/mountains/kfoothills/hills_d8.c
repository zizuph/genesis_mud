#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_d7","west",0);
    add_exit(HILLS_PATH + "hills_e7","northwest",0);
    add_exit(HILLS_PATH + "hills_e8","north",0);
    add_exit(HILLS_PATH + "hills_d9","east",0);
    add_exit(HILLS_PATH + "hills_c9","southeast",0);
    add_exit(HILLS_PATH + "hills_c8","south",0);
    add_exit(HILLS_PATH + "hills_c7","southwest",0);

    reset_room();

}
