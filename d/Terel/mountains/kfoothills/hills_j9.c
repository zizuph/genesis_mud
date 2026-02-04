#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_j8","west",0);
    add_exit(HILLS_PATH + "hills_k9","north",0);
    add_exit(HILLS_PATH + "hills_i9","south",0);
    add_exit(HILLS_PATH + "hills_i8","southwest",0);

    reset_room();

}
