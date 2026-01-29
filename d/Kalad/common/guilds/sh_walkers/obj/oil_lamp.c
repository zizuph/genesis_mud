/*
 * /d/Kalad/common/guilds/sh_walkers/obj/oil_lamp.c
 * Created By : Rico 7.01.97
 * First Modif:
 */

inherit "/std/new_torch";
 
#include <stdproperties.h>
 
void create_torch()
{
    ::create_torch();

    set_name(({"oil lamp","lamp"}));

    set_weight(110);
    set_strength(3);
    set_max_fuel(3600);
 
    add_prop("_obj_i_takes_oil", 1);
}

