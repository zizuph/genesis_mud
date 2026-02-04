/*
 * A mace for the guards of Calathin.
 * Coded by Shinto 10-7-98
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"mace","club"}));
    set_adj(({"heavy", "steel"}));
    set_short("heavy steel mace");
    set_pshort("heavy steel maces");
    set_long("The solid steel mace head is covered with imposing "+
             "spikes, attached to the handle with a metal "+
             "chain. The hardwood handle is further enhanced by "+ 
	     "the leather straps serving as a comfortable handle.\n");
    set_default_weapon(35, 35, W_CLUB, W_BLUDGEON, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 600);
}

