#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_c1","west",0);
    add_exit(HILLS_PATH + "hills_c3","east",0);
    add_exit(HILLS_PATH + "hills_d2","north",0);
    add_exit(HILLS_PATH + "hills_b2","south",0);
    add_exit(HILLS_PATH + "hills_d3","northeast",0);
    add_exit(HILLS_PATH + "hills_b3","southeast",0);
    add_exit(HILLS_PATH + "hills_b1","southwest",0);

    reset_room();
}
