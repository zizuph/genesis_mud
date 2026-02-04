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
    set_long(query_long() + "A large boulder to your southwest " +
        "blocks passage in that direction.\n");
    add_item(("boulder"), "A large chunk of solid rock " +
        "and you notice that the northern face has been " +
        "polished smooth by someone or something.\n");

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_f4","west",0);
    add_exit(HILLS_PATH + "hills_g4","northwest",0);
    add_exit(HILLS_PATH + "hills_g5","north",0);
    add_exit(HILLS_PATH + "hills_f6","east",0);
    add_exit(HILLS_PATH + "hills_e6","southeast",0);
    add_exit(HILLS_PATH + "hills_e5","south",0);

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
