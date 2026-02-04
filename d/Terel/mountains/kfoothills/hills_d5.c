#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_d4","west",0);
    add_exit(HILLS_PATH + "hills_e4","northwest",0);
    add_exit(HILLS_PATH + "hills_e5","north",0);
    add_exit(HILLS_PATH + "hills_e6","northeast",0);
    add_exit(HILLS_PATH + "hills_d6","east",0);
    add_exit(HILLS_PATH + "hills_c6","southeast",0);
    add_exit(HILLS_PATH + "hills_c5","south",0);
    add_exit(HILLS_PATH + "hills_c4","southwest",0);

    reset_room();

}
