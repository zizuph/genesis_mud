#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_a2","west",0);
    add_exit(HILLS_PATH + "hills_a4","east",0);
    add_exit(HILLS_PATH + "hills_b4","northeast",0);
    add_exit(HILLS_PATH + "hills_b2","northwest",0);
    add_exit(HILLS_PATH + "hills_b3","north",0);

    reset_room();

}
