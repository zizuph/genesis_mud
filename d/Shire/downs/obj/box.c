/*
 * Secret box in barrows for artifact quest.
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


    set_name("box");
    add_name(({"interior", "box", "hole"}));

    set_short("box");
    set_long("This is a small hidden box inside the wall. It is made of stone and used to hide artifacts and other items.\n");
}