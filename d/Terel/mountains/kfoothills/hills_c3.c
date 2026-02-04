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
    set_long(query_long() + "A large boulder to your southeast " +
        "blocks passage in that direction.\n");
    add_item(("boulder"), "A large chunk of solid rock " +
        "with small flecks of some kind of ore embedded within.\n");

	add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
    add_exit(HILLS_PATH + "hills_c2","west",0);
    add_exit(HILLS_PATH + "hills_c4","east",0);
    add_exit(HILLS_PATH + "hills_d3","north",0);
    add_exit(HILLS_PATH + "hills_b3","south",0);
    add_exit(HILLS_PATH + "hills_d4","northeast",0);
    add_exit(HILLS_PATH + "hills_b2","southwest",0);
    add_exit(HILLS_PATH + "hills_d2","northwest",0);

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
