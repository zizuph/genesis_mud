inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
 
void
create_room()
{
    set_short("A dim bedroom in a cottage.");
    set_long("In this dim bedroom, you cannot make out many " +
        "details, though you can see a large bed placed carefully " +
        "in the corner. Towels are spread around the bed, a bowl " +
        "rests on the floor beside them. The main room of the " +
        "cottage is back north.\n");
 
    add_item(({"bedroom"}),
        "This bedroom is obviously for a very ill hobbit. The " +
        "towels are soaked in some sort of medicinal concoction, " +
        "but now the bowl is empty. In the corner, you think you " +
        "see an old sick hobbit, apparently on his deathbed.\n");
    add_item(({"sick hobbit", "old sick hobbit", "old hobbit"}),
        "He looks very ill and on the verge of death. His " +
        "skin is pale and clammy looking. His eyes are " +
        "sunken and some wispy strands of hair on his head.\n");
    add_item(({"towels"}),
        "Dry towels are stacked alongside the bed and spread " +
        "across the bed. Elsewhere, you see some towels soaking " +
        "in a bowl of water and herbs. They are plain " +
        "white cotton towels\n");
    add_item("wet towels",
        "They are soaking in a bowl. They are moist and used to " +
        "clean the sick hobbit and to help lower his " +
        "temperature.\n");
    add_item("dry towels",
        "Some towels are stacked along side and spread across " +
        "the bed.\n");
    add_item(({"medicinal conncotion", "bowl of water and herbs"}),
        "The substance is dark colored with various herbs " +
        "floating in it and on its surface. A faint odor rises " +
        "from it, filling the air with its fragrance.\n");
    add_item("bowl",
        "The bowl is brown and made of pottery. It is full " +
        "of water and herbs. and sits on the table, next to " +
        "the bed.\n");
    add_item("table",
        "The table small and is placed next to the bed. It is " +
        "simple in construction but sturdy. Some towels and a " +
        "bowl full of water and herbs sit on it.\n");
    add_item("bed",
        "The bed is simple but looks large enough for two or " +
        "three hobbits. A sick hobbit lies on it under some " +
        "blankets and towels.\n");
    add_item(({"blanket", "blankets", "covers", "comforters"}),
        "The blankets are simple with floral designs, but look " +
        "warm. They cover the bed.\n");
    add_item(({"floral designs"}),
        "The designs are of wild flowers and decorate the " +
        "blankets on the bed.\n");
    add_item(({"floor", "ground"}),
        "The floor is bare except for a a small rug near the " +
        "bed.\n");
    add_item(({"rug", "small rug", "thread-bare rug", 
            "small thread-bare rug"}),
        "The rug is oval in shape and made of twisted fabric. " +
        "ears of use, the rug is thread-bare witha couple of " +
        "in it.\n");
    add_item(({"walls", "wall"}),
        "The walls are bare and dull looking.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling is bare with nothing of interest up there.\n");
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(MICH_DIR + "petunia_house","north",0,1);
}
 
/*
void
reset_room()
{
    add_stuff();
}
 
void
add_stuff()
{
    object hob;
 
    if (!present("_mardil_"))
    hob = clone_object(MICH_DIR+"npc/mardil");
    hob->move(TO);
 
}
*/
