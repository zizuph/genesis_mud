/*
 * Tomb dweller shield: top of the line model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#define TEREL_TEMPERED_SHIELD "_terel_tempered_shield"

create_terel_armour()
{
     set_name(({"shield"}));
     set_short("tempered shield");
     set_long("Its a shiny tempered shield used by tomb dwellers.\n");
     set_adj(({"tempered"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

     set_default_armour(39, A_SHIELD, 0, 0);
}

mixed
wear_terel_armour(object obj)
{
    if (TO->query_prop(OBJ_I_BROKEN))
        TP->remove_prop(TEREL_TEMPERED_SHIELD);
    
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

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    from->remove_prop(TEREL_TEMPERED_SHIELD);    
}

