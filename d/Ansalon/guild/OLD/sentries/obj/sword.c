/*
 * File Name        : sword.c
 * By               : Elmore and Boron
 * Inspiration from : Occ_fighter Guild by Unknow.
 * Date             : March 2001
 *
 */

#pragma strict_types

inherit "/std/weapon";

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <formulas.h>
#include <wa_types.h>

string
query_auto_load()
{
    return MASTER_OB(TO) + ":";
}

void
create_object()
{
    set_name("sword");
    add_name(GUILD_EMBLEM_ID);
    set_adj("old");
    add_adj("ceremonial");
    set_short("elegant ceremonial sword");
    set_long("@@my_long");

    add_prop(OBJ_M_NO_DROP, "You cannot drop the sword.\n");
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  500);
    remove_prop(OBJ_I_VALUE);
}

string
my_long()
{
    return "ENTER DESC FOR SWORD.\n";
}
