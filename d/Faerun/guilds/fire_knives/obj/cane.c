/*
 * Walking cane for questnpc2.
 *
 * Nerull 2019 
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

void
create_faerun_weapon()
{

    set_name("cane");
    set_adj("sturdy");
    set_adj("wooden");
    
    set_short("sturdy wooden cane");
    
    set_long("This is a sturdy wooden cane made for walking. Though, "
    +"it could probably be used as a solid weapon against brigands "
    +"and bandits judging by its somewhat strong construction.\n");

    set_hit(25);
    set_pen(26);
    set_wt(W_CLUB); 
    set_dt(W_BLUDGEON); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,26));

    set_hands(W_ANYH); 
}
