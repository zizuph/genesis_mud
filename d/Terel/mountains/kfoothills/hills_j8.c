#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";
object kobold;
object kobold2;
object kobold3;

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_k9","northeast",0);
    add_exit(HILLS_PATH + "hills_j9","east",0);
    add_exit(HILLS_PATH + "hills_i9","southeast",0);
    add_exit(HILLS_PATH + "hills_i8","south",0);

    reset_room();

}

void
reset_room()
{
    if(!kobold)
    {
        kobold = clone_object(NPC + "newKobold");
        kobold->move(TO);

        kobold2 = clone_object(NPC + "newKobold");
        kobold2->move(TO);
    
        kobold3 = clone_object(NPC + "newKobold");
        kobold3->move(TO);
    }
}
