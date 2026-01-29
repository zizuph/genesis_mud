/*
 *      /d/Gondor/guilds/rangers/obj/old_bin.c
 *    This bin is for collecting non-guild
 *    items
 *
 */
inherit "/std/container";

#include <formulas.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_container()
{
    set_short("large wooden junk bin");
    set_name("bin");

    set_adj(({"wooden", "large", "junk"}));
    set_long("This large bin is made of sturdy oak. Nicks and scratches "
        + "can be seen from where Rangers have hastily thrown in "
        + "miscellaneous items. Its purpose is to hold items not worthy " 
        + "of being placed in the weapons or armours racks for " 
        + "safe keeping. Items placed in this bin will not be " 
        + "added to the equipment list.\n");

    add_prop(OBJ_M_NO_GET, "The bin is too heavy. All you manage to do " +
         "is hurt your back.\n");
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_VOLUME,     5000);
    add_prop(CONT_I_WEIGHT,     25000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     0);
}

