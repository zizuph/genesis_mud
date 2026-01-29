/*
 * Knife coded by Rastlin, modified by Teth Jan 18 1997
 */

inherit "/std/weapon";

#include <wa_types.h>
#include "../local.h"

nomask
create_weapon() 
{
    set_name("dagger");
    set_adj("rusty");
    add_name(({"knife","weapon"}));
    set_short("rusty dagger");
    set_pshort("rusty daggers");
    add_pname(({"knives","weapons"}));
    set_long("It is a rusty dagger, that could do a fair amount of " +
        "damage to an unsuspecting opponent.\n");
    set_default_weapon(5, 10, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME,450);
}
