inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("kitchen");
    set_long(BSN(
        "This is the kitchen of this small home. Another, larger wood stove "
      + "burns here, and cupboards line the walls. There is a large basin "
      + "which is full of water, and a square window cut into the stone wall. "
      + "The only furnishings consist of a small cutting-block and two tall "
      + "stools."));
    add_item(({"stove","wood stove","large stove"}),BSN(
        "This large stove is cubical and bears a stained cooking surface. "
      + "Pots sit upon the stove and beside it. You feel heat radiating from "
      + "the stove and see the dull flicker of fire around the edges of the "
      + "stove door. The battered chimney leads through the wall, carrying "
      + "most of the smoke outside."));
    add_item(({"cupboards","cupboard"}),BSN(
        "These worn, old cupboards are of poor construction. They hold the "
      + "meager utensils and vessels that the family uses in this kitchen "
      + "and to eat on the dining table to the south."));
    add_item(({"basin","large basin"}),BSN(
        "This large, iron basin collects rainwater from the roof of the house "
      + "and stores it for the family to use. A wooden gutter diverts water "
      + "through the open window and into the basin."));
    add_item(({"cutting-block","cutting block","block"}),BSN(
        "This cube of wood is marred and scored by the innumerable cuts of "
      + "daily kitchen-work. It sits in the center of the room, accessible at "
      + "all sides."));
    add_item(({"stools","stool","tall stools","tall stool"}),BSN(
        "These stools are of common craftsmanship, made of a cheap wood. They "
      + "are tall to facilitate stirring at the stove and cutting at the "
      + "cutting-block while sitting. One sits at the wood stove, and another "
      + "at the block."));
    add_item(({"water"}), "The water is cool and clear.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    set_wealth(0);
    set_side("north");
    set_circle("First Circle");

    add_window("The window has no shutters, but there is a wooden " +
        "gutter leading to the metal basin.");
    add_walls("They radiate heat from the stove.");
    add_ceiling("It is surprisingly low.");
    add_floor("The floor is well cleaned and polished.");

    add_exit(MINAS_DIR + "houses/citizens/h2r1sn3crc1","south",0,0);
}
