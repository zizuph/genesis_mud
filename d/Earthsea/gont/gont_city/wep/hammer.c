#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("hammer");
    add_name("__es_hammer__");
    set_adj(({"rusty", "iron"}));
    set_short("rusty iron hammer");
    set_long("A large rusty iron hammer, obviously well used.\n");
    set_default_weapon(28, 28, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VALUE, 150);
}
