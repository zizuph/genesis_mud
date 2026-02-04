#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_b1","west",0);
    add_exit(HILLS_PATH + "hills_b3","east",0);
    add_exit(HILLS_PATH + "hills_c3","northeast",0);
    add_exit(HILLS_PATH + "hills_c1","northwest",0);
    add_exit(HILLS_PATH + "hills_c2","north",0);
    add_exit(HILLS_PATH + "hills_a2","south",0);
    add_exit(HILLS_PATH + "hills_a3","southeast",0);
    add_exit(HILLS_PATH + "hills_a1","southwest",0);

    reset_room();

}
