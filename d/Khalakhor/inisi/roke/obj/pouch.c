/*
 * pouch.c
 *
 * Used in obj/fishingnet.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";

#include <money.h>
#include <stdproperties.h>

void
create_container()
{
    set_name("pouch");
    set_short("leather pouch");
    set_adj("leather");
    set_long("This is a leather pouch used for keeping money.\n");
    add_prop(CONT_I_WEIGHT, 100);      /* weight 100 g */
    add_prop(CONT_I_MAX_WEIGHT, 1100); /* can hold 1 kg */
    add_prop(CONT_I_VOLUME, 100);      /* it's volume is 0.1 l */
    add_prop(CONT_I_MAX_VOLUME, 1100); /* holds 1 litre */
    add_prop(OBJ_I_VALUE, 40);
    MONEY_MAKE_SC(10)->move(this_object()); /* put 10 silver in it */
}
