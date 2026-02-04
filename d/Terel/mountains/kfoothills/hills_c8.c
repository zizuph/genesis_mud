#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"
inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_c7","west",0);
    add_exit(HILLS_PATH + "hills_c9","east",0);
    add_exit(HILLS_PATH + "hills_d8","north",0);
    add_exit(HILLS_PATH + "hills_d9","northeast",0);
    add_exit(HILLS_PATH + "hills_d7","northwest",0);

    reset_room();

}
