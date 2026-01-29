/*
 * Greaves used by trolls in Trollshaws
 * -- Finwe October 2001
 */

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("light");
    add_adj("steel");
    set_short("light steel greaves");
    set_pshort("light steel greaves");
    set_keep(); 

    set_long("These are a pair of "+short()+". They are worn " +
    "on the legs and offer protection to the wearer. These " +
    "have been stolen by the trolls in one of their many raids.\n");
    set_ac(40);
    add_prop(OBJ_I_WEIGHT,2500);
    
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_VALUE, 750+random(500));
}

void init_recover(string arg)
{
    init_arm_recover(arg);
}

string query_recover()
{
    return MASTER + ":" + query_arm_recover();
} 
