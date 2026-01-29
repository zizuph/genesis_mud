#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("cap");
    set_adj(({"cocked", "sailor's"})),
    set_short("sailor's cocked cap");
    set_long("This is a cocked cap with a wide brim "+
        "turned up all around, typically worn by sailors.\n");
    set_at(A_HEAD);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 35);
    add_cmd_item((({"cap", "sailor's cap", "cocked cap",
          "sailor's cocked cap"})), "tip", "@@tip_cap");
}

public int
tip_cap()
{
    object tp = query_worn();

    if(!objectp(tp))
    {
        return notify_fail("You are not wearing the cap.\n");;
    }

    write("You tip your cocked cap in salute.\n");
    tell_room(environment(tp), QCTNAME(tp) + " tips " +
        tp->query_possessive() + " " + query_short() + 
        " in salute.\n", ({tp}));
    return 1;
}
