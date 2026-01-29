#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the messhall.");
    set_em_long("As you look around the messhall, you notice the sharp smell of roasted " +
        "meat. Rows of long tables accompanied by long wooden benches fill the room. " +
        "A large fireplace along the northern wall heats up the room and casts dancing " +
        "shadows upon the walls. You can see the kitchen through the doorway to your " +
        "south while looking north you notice a smaller, private eating area. Going " +
        "east from here will bring you into the yard outside.\n");


    add_item( ({"table", "tables", "long table", "long tables"}),
        "Lined up in perfect rows, tables stretch from one end of the room to the " +
        "other. Each table shows some wear but they still serve their purpose well. " +
        "On each side of every table sits a long wooden bench.\n");

    add_item( ({"bench", "wooden bench", "benches", "wooden benches", "long wooden bench",
                "long wooden benches", "long bench", "long benches"}),
        "These long wooden benches are made from the same wood as the tables. Each bench " +
        "bears the marks that guards and armour will dig into a piece of wood after " +
        "enough use. A couple of the benches have been pulled close to the fire forming " +
        "a semi circle around the fireplace.\n");

    add_item( ({"shadow", "shadows"}),
        "The light from the fire casts shadows upon the wall that dance and jump " +
        "in time with the flickering flames.\n");
   
    add_item( ({"fireplace", "large fireplace"}),
        "A large stone fireplace is embedded in the northern wall. Made from large " +
        "rocks, it does not look as though a lot of care was taken during construction. " +
        "A roaring fire blazes within, showering the room in light.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "The walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather.\n"); 


    add_exit("yard_07.c","east");
    add_exit("umesshl.c","north");
    add_exit("kitchen.c","south");
}
