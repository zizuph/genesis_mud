/*
 * /d/Gondor/guilds/morgulmage/obj/tbarrel.c
 * A barrel for the Tuvale to store items in
 * Varian 2016
 */

inherit "/std/container";
#include <stdproperties.h>

void
create_container()

{
    set_name("barrel");
    set_short("large wooden barrel");
    set_pshort("large wooden barrels");
    set_long("This large barrel is made from wood and has clearly seen " +
        "better days. The sides and edges are all chipped and broken, " +
        "while the wood itself has begun to rot on the sides. It " +
        "appears as if someone has been using this barrel for the " +
        "storage of anything and everything.\n");

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_MAX_WEIGHT,1000000);
    add_prop(CONT_I_VOLUME, 1);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(OBJ_M_NO_GET, "Some strange force has attached the barrel " +
        "to the ground, preventing you from taking it.\n");
}