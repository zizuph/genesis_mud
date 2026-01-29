/*
 * Component pouch
 *
 * Ashlar, 01 Jul 98
 */

inherit "/std/receptacle";
inherit "/lib/keep";
// wearable item also!

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_receptacle()
{
    set_name("pouch");
    set_pname("pouches");
    
    set_adj("soft");
    add_adj("leather");

    set_short("soft leather pouch");
    set_pshort("soft leather pouches");

    set_long("It is a soft leather pouch, ideal for holding " +
    "spell components.\n");

    add_prop(OBJ_I_VALUE, 100);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 1000);
    remove_prop(CONT_I_RIGID);

    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_keep(1);
}

int
prevent_enter(object ob)
{
    if ((function_exists("create_object",ob) == "/std/herb") ||
        (function_exists("create_food",ob) == "/std/leftover") ||
        (function_exists("create_heap",ob) == "/std/coins"))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)

{
    init_keep_recover(arg);
}

