/*
 * Knife coded by Rastlin, modified by Teth Jan 18 1997
 */

inherit "/std/weapon";

#include <wa_types.h>
#include "../local.h"

nomask
create_weapon() 
{
    set_name("knife");
    set_pname("knives");
    set_adj("shining");
    add_name(({"dagger","weapon"}));
    set_short("shining knife");
    set_pshort("shining knives");
    add_pname(({"daggers","weapons"}));
    set_long("It is a shining knife, stained with the stench of goblin.\n");
    set_default_weapon(10, 10, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME,450);
}
