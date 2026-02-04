#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_f8","west",0);
    add_exit(HILLS_PATH + "hills_g8","northwest",0);
    add_exit(HILLS_PATH + "hills_g9","north",0);
    add_exit(HILLS_PATH + "hills_f10","east",0);
    add_exit(HILLS_PATH + "hills_e8","southwest",0);


    reset_room();
}
