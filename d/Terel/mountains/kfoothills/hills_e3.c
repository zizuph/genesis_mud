#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_e2","west",0);
    add_exit(HILLS_PATH + "hills_f3","north",0);
    add_exit(HILLS_PATH + "hills_f4","northeast",0);
    add_exit(HILLS_PATH + "hills_e4","east",0);
    add_exit(HILLS_PATH + "hills_d4","southeast",0);
    add_exit(HILLS_PATH + "hills_d3","south",0);
    add_exit(HILLS_PATH + "hills_d2","southwest",0);

    reset_room();

}
