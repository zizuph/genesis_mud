/*
 * Tomb dweller shield: top of the line model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#define TEREL_TEMPERED_SHIELD "_terel_tempered_shield"

void
create_terel_armour()
{
     set_name(({"shield"}));
     set_short("shiny tempered shield");
     set_long("It is a shiny shield cast with an iron alloy that "+
        "has been tempered to give it greater impact resistance "+
        "than normal steel. The craftsmanship is "+
        "characteristic of the tomb dwellers.\n");
     set_adj("tempered");
     add_adj(({"shiny", "alloy", "metal", "tomb", "dweller"}));

     set_default_armour(39, A_SHIELD, 0, 0);
	 set_shield_slot(({ A_BODY, A_LEGS }));
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

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    from->remove_prop(TEREL_TEMPERED_SHIELD);    
}

