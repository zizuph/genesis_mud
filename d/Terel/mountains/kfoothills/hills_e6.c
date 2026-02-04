#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_e5","west",0);
    add_exit(HILLS_PATH + "hills_f5","northwest",0);
    add_exit(HILLS_PATH + "hills_f6","north",0);
    add_exit(HILLS_PATH + "hills_f7","northeast",0);
    add_exit(HILLS_PATH + "hills_e7","east",0);
    add_exit(HILLS_PATH + "hills_d7","southeast",0);
    add_exit(HILLS_PATH + "hills_d6","south",0);
    add_exit(HILLS_PATH + "hills_d5","southwest",0);

    reset_room();

}
