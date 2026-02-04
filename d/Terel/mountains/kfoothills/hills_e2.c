#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

object rock1;
object rock2;
object rock3;

public void
create_room()
{
    ::create_room();

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_e3","east",0);
    add_exit(HILLS_PATH + "hills_d3","southeast",0);
    add_exit(HILLS_PATH + "hills_d2","south",0);

    reset_room();

}

void
reset_room()
{
    if(!rock1)
    {
        rock1 = clone_object("/d/Shire/common/obj/random_rock");
        rock1->move(TO);

        rock2 = clone_object("/d/Shire/common/obj/random_rock");
        rock2->move(TO);

        rock3 = clone_object("/d/Shire/common/obj/random_rock");
        rock3->move(TO);
    }
}
