/*
 * Tomb dweller shield: base model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"shield"}));
     set_short("iron shield");
     set_long("Its a heavy iron shield used by tomb dwellers.\n");
     set_adj(({"iron"}));

     set_default_armour(19, A_SHIELD, 0, 0);
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
