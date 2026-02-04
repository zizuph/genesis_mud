




/*
 * z_cloak.c
 *
 * Zasultra's cloak.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("robe");
    set_adj("dark");
    set_long("It's a dark, almost black, robe of very high quality. " +
             "A large eye has been embroidered with silver thread " +
             "on its back. " +
             "It looks as if it was made for a woman.\n");
    set_default_armour(32, A_ROBE, 0, 0);
    set_am(({ 2, 2, -4}));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 600);
}

public mixed
wear_terel_armour(object ob)
{
    if (TP->query_gender() == FEMALE) return 0;
    
    return "The " + ob->short() + " does not fit you.\n";
}

