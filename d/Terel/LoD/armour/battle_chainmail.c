




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * battle_chainmail.c
 *
 * worn by captains and lietenants in LoD.
 *
 * a dark legion chainmail redhawk 921111
 * Modified by Sorgum 941026
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
    set_name("chainmail");
    set_short("battle chainmail");
    set_pname("battle chainmails");
    add_pname("chainmails");
    set_long("It's a battle chainmail of good quality that is worn by " +
	     "soldiers in the legion of darkness, the quality of the " +
	     "armour differs on base of the rank the bearer " +
	     "has in the legion of darkness.\n");
    set_adj(({"battle"}));

    set_default_armour(45, A_BODY, 0, 0);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,    1);
   add_prop(OBJ_S_WIZINFO, "This chainmail is augmented to "+
                  "protect better then normal chainmail. 45 45.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" was crafted to withstand physical attacks" +
           "better then normal chainmail.\n",20}));
    add_prop(OBJ_I_VALUE,            900);
    add_prop(OBJ_I_WEIGHT,          8000);
}
