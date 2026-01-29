/*
 * Closet in Tom Bombadills house
 * Ruthlessly borrowed indefinately from the fireplace compartment in 
 * the Solace ruins
 * -- Finwe January 2002
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_container()
{
    /* This compartment is suposed to be invisible and only accessable
     * under the propper circumstances.
     */

    object comp;

    add_prop(CONT_I_WEIGHT,     10000); 
    add_prop(CONT_I_VOLUME,       50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME,   60000);
    add_prop(CONT_I_RIGID,            1);
    add_prop(OBJ_I_NO_GET,            1);
    add_prop(CONT_I_TRANSP,           1);
    set_no_show_composite(0);


    set_name("closet interior");
    add_name(({"interior", "closet"}));

    set_short("closet interior");
    set_long("This is the inside of the closet under the stairs. " +
        "It is full of shelves and compartments, loaded with " +
        "boxes, small crates, and chests.\n");
    add_item(({"boxes"}),
        "They are made of wood and are all closed. They look " +
        "heavy and are closed. The boxes are stacked on the " +
        "shelves and floor.\n");
    add_item(({"small crates", "crates", "chests", "small chests"}),
        "They are made of wood with iron bands around them. They " +
        "are locked and stacked on the floor.\n");
}