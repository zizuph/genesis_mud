#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the officer's messhall.");
    set_em_long("A beautiful wooden table sits in the middle of this " +
        "room. Where crude wooden benches had sufficed as seating in " +
        "the general messhall, here each officer gets a separate " +
        "chair. The fireplace set into the southern wall casts " + 
        "light into the room and shadows upon the walls. You can see " +
        "the general messhall through the doorway in the southern " +
        "wall.\n");


    add_item( ({"table", "wooden table", "beautiful wooden table", "beautiful table"}),
        "A beautiful oak table sits in the middle of the room. Its smooth " +
        "polished surface is meticulously clean and free of scratches. The legs " +
        "of the table have been carved to look like those of a huge animal. Huge " +
        "claws spread out from the feet and help to stablilize the structure.\n");

    add_item( ({"chair", "chairs"}),
        "Wooden chairs surround the beautiful table in the middle of the room. " +
        "A thick cusion has been placed upon each seat to help make dining here " +
        "a comfortable experience.\n");

    add_item( ({"shadow", "shadows"}),
        "The light from the fire casts shadows upon the wall that dance and jump " +
        "in time with the flickering flames.\n");

       add_item( ({"fireplace", "large fireplace"}),
        "A large stone fireplace is embedded in the southern wall. Made from large " +
        "rocks, it does not look as though a lot of care was taken during construction. " +
        "A roaring fire blazes within, showering the room in light.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "The walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather.\n"); 

    add_item( ({"cusion", "thick cusions", "thick cusions", "cusions"}),
        "Thick cusions pad the wooden chairs. They are embroidered with thread and " +
        "stuffed with wool.\n");


    add_exit("lmesshl.c","south");
}
