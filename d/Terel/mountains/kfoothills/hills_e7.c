#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_e6","west",0);
    add_exit(HILLS_PATH + "hills_f6","northwest",0);
    add_exit(HILLS_PATH + "hills_f7","north",0);
    add_exit(HILLS_PATH + "hills_f8","northeast",0);
    add_exit(HILLS_PATH + "hills_e8","east",0);
    add_exit(HILLS_PATH + "hills_d8","southeast",0);
    add_exit(HILLS_PATH + "hills_d7","south",0);
    add_exit(HILLS_PATH + "hills_d6","southwest",0);

    reset_room();

}
