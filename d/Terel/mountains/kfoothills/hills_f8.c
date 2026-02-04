#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_f7","west",0);
    add_exit(HILLS_PATH + "hills_g7","northwest",0);
    add_exit(HILLS_PATH + "hills_g8","north",0);
    add_exit(HILLS_PATH + "hills_g9","northeast",0);
    add_exit(HILLS_PATH + "hills_f9","east",0);
    add_exit(HILLS_PATH + "hills_e8","south",0);
    add_exit(HILLS_PATH + "hills_e7","southwest",0);

    reset_room();
}
