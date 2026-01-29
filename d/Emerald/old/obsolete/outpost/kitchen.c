#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the kitchen.");
    set_em_long("You have entered the room where all the food for the soldiers " +
        "gets prepared. A long table covered with cooking tools and utensils " +
        "lines the southern wall. Within the firepit built into the western wall, " +
        "a fire blazes and floods the room with light. A large basin of water " +
        "filled with dirty dishes and platters sits along the eastern wall. " +
        "You can see the main dining area through the open doorway in the " +
        "northern wall.\n");


    add_item( ({"table", "long table", "long wooden table", "wooden table"}),
        "Along the southern wall, a long wooden table with a thick top is used " +
        "in the preparation of food. Scattered along the top of the table lie " +
        "many implements and tools used to help the cooks with their chores.\n");

    add_item( ({"tools", "cooking tools", "utensils"}),
        "Assorted cooking utensils cover the table. Among them you notice a " +
        "bunch of large wooden spoons and some sharp knives.\n");

    add_item( ({"large wooden spoon", "large wooden spoons", "wood spoon", "wooden spoon",
                "wood spoons", "wooden spoons", "spoon", "spoons", "large spoon", 
                "large spoons"}),
        "The spoons, some clean, some crusted with dried foodstuffs, lie discarded upon " +
        "the table.\n");

    add_item( ({"knife", "sharp knife", "sharp knives", "knives"}),
        "Upon closer inspection, you realize that none of the knives are very sharp. " +
        "The are made of thin metal and have wooden handles.\n");

    add_item( ({"basin", "large basin", "water"}),
        "A deep wooden basin filled with brackish water sits along the eastern wall. " +
        "Judging from the piles of dishes in the basin, the cook has not had a chance " +
        "to clean the mess made from today's meals.\n");

    add_item( ({"dishes", "dirty dishes", "platter", "platters"}),
        "Large platters and many dishes fill the basin. Sauces and scraps of food are " +
        "caked onto those surfaces not submerged in the brackish brown water.\n");

    add_item( ({"firepit", "fire"}),
        "A roaring fire blazes within the firepit. Steam rises from a black " +
        "pot which hangs over the flames.\n");

    add_item( ({"pot", "steaming pot", "black pot", "black steaming pot"}),
        "Water boils inside an iron pot which swings on a chain over the fire.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "The walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather.\n"); 


    add_exit("lmesshl.c","north");
}
