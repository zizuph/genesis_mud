/*
 * /d/Genesis/lebennin/obj/sack.c
 *
 * Recoded using /d/Genesis/std/pack.c
 * by Olorin, 8-Dec-1996
 *
 * Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_wearable_pack() 
{
    set_name("sack");
    set_pshort("soiled sacks");
    set_adj("soiled");
    set_long("This soiled sack looks like it has been used often and never washed. " +
	     "It can be worn on the back. " +
	     "You may use the `fill' and `empty' commands on it.\n");
    add_prop(CONT_I_WEIGHT,      2000);   /* It weighs 2 Kg              */
    add_prop(CONT_I_MAX_WEIGHT, 27000);   /* It can contain up to 25 Kg  */
    add_prop(CONT_I_VOLUME,      3000);   /* It measures 3 Ltr           */
    add_prop(CONT_I_MAX_VOLUME, 28000);   /* It can contain 25 Ltr       */
    add_prop(OBJ_I_VALUE, 144);           /* Value 1 gc                  */

    set_mass_storage(1);
}

public string
query_recover()
{
    return MASTER + ":" + 
	query_container_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
}
