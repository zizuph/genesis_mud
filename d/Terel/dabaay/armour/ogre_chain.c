/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_chain.c
 *
 * worn by the Dunker.
 *
 * Goldberry, April 2000
 */

#include <wa_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    int aclass;

    aclass = 55+random(5);
    set_armour_size(LARGE);
    set_name("chainmail");
    set_short("heavy iron chainmail");
    set_pname("heavy iron chainmails");
    add_name("armour");
    set_adj(({"heavy","iron"}));
    set_long(
        "A heavy shirt of iron chainmail. The links in the chainmail "+
        "are made from dark iron, and have a high temper. The size of "+
        "this shirt is quite large.\n");

    set_default_armour(aclass, A_BODY, 0, 0);
    set_am(({0,2, -1}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"Enchanted iron chainmail worn by Dunker "+
       "in Terel. Armour class of 55 + random(5). Can only be worn "+
       "by giant or ogre-sized creatures.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The "+short()+" is enchanted to protect from physical blows.\n",40}));

    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(aclass, A_BODY)) * 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/6);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(aclass) + 1000);    
}