/*
 * fat.c
 *
 * Used in npc/child.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Slice of fat, Used in Kato quest */

#pragma save_binary
#pragma strict_types

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>

string namn;

void
create_food()
{
    namn = "";
    set_name(({"fat", "piece"}));
    set_short("slice of fat");
    set_pshort("slices of fat");
    set_long("A piece of greasy fat torn out from a child \n");
    set_adj("greasy");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    set_amount(64);
}

void
enter_env(object dest, object from)
{
    ::enter_inv(dest, from);
    if (!from)
        return;
    if (namn == "" && query_ip_number(dest))
        namn = dest->query_real_name();
}

string
query_namn()
{
    return namn;
}
