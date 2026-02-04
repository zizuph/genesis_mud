#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_h7","north",0);
    add_exit(HILLS_PATH + "hills_h8","northeast",0);
    add_exit(HILLS_PATH + "hills_g8","east",0);
    add_exit(HILLS_PATH + "hills_f8","southeast",0);
    add_exit(HILLS_PATH + "hills_f7","south",0);
    add_exit(HILLS_PATH + "hills_f6","southwest",0);

    reset_room();

}
