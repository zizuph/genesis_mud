/*
 * Collar worn by the haradrim captains
 * -- Finwe, July 2005
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
    set_name("collar");
    add_name("armour");
    set_pname("collars");
    set_adj("polished");
    add_adj("bronze");
    set_short("polished bronze collar");
    set_pshort("polished bronze collars");
    set_long("This is a bronze collar that has been polished and glows " +
        "in the light. It has spikes, and wraps around the neck to protect " +
        "it during battles.\n");

    set_ac(30);
    set_am(({1,1,-2}));
    set_at(A_NECK);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME,  600);
    add_prop(OBJ_I_VALUE,   122+random(40));
    set_keep();
}  
