/*
 * /d/Faerun/guilds/warlocks/obj/vial.c
 *
 * Finwe 2018
 */

inherit "/std/container";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define TYPE    ({"demon-face", "horned", "snake-shaped" })
#define STYLE   ({"smooth", "dirty", "small" })

string  a_type  = ONE_OF_LIST(TYPE),
        a_style = ONE_OF_LIST(STYLE);
        
public void
create_container()
{
    set_name("vial");
    add_name(({"_std_potion_vial"}));
    set_adj(a_style);
    set_adj(a_type);
    set_adj("empty");
    set_short("empty " + a_style + " " + a_type + " vial");
    set_long("An empty vial. You could fill a potion into it.\n");
    add_prop(CONT_I_MAX_VOLUME, 1100);
    add_prop(CONT_I_MAX_WEIGHT, 1250);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 24);
}


public string
query_recover()
{
    return MASTER + ":" + a_style + " " + a_type;
}
