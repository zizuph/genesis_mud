/*
 * Tomb dweller shield: good model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#define TEREL_TEMPERED_SHIELD "_terel_tempered_shield"

create_terel_armour()
{
     set_name(({"shield"}));
     set_short("alloy shield");
     set_long("Its a metal alloy shield used by tomb dwellers.\n");
     set_adj(({"alloy"}));

     set_default_armour(29, A_SHIELD, 0, 0);
}

mixed
wear_terel_armour(object obj)
{
    if(TP->query_prop(TEREL_TEMPERED_SHIELD))
    {
        write("You can't wear two of these shields, they are too big!\n");
        return -1;
    }
    TP->add_prop(TEREL_TEMPERED_SHIELD, 1);
    return 0;
}

mixed
remove(object obj)
{
    TP->remove_prop(TEREL_TEMPERED_SHIELD);
    return 0;
}


public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
