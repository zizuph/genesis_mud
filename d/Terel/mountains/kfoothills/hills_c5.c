#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"

inherit HILLS_PATH + "default_hills";

object kobold;
object kobold2;
object kobold3;
object rock1;
object rock2;
object rock3;

public void
create_room()
{
    ::create_room();
    set_long(query_long() + "A large boulder to your southeast " +
        "blocks passage in that direction.\n");
    add_item(("boulder"), "A large chunk of solid rock " +
        "and you notice that the northwestern face has been " +
        "polished smooth by someone or something.\n");

    add_prop(ROOM_S_MAP_FILE, "kobold_camp.txt");
	add_exit(HILLS_PATH + "hills_c4","west",0);
    add_exit(HILLS_PATH + "hills_c6","east",0);
    add_exit(HILLS_PATH + "hills_d5","north",0);
    add_exit(HILLS_PATH + "hills_b5","south",0);
    add_exit(HILLS_PATH + "hills_d6","northeast",0);
    add_exit(HILLS_PATH + "hills_d4","northwest",0);
    add_exit(HILLS_PATH + "hills_b4","southwest",0);

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
