/*
 * Thay staff for questnpc3.
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

    set_name("staff");
    add_name("quarterstaff");
    
    set_adj("ornate");
    add_adj("jeweled");
    
    set_short("jeweled ornate staff");
    
    set_long("This is an elegant quarterstaff made of "
    +"polished black oak. The bottom of the staff is shod "
    +"with a silvery knob. The handle of the staff is polished "
    +"black oak with silvery metal tendrils twisting along "
    +"it's surface in a pattern resembling a lightning bolt. On "
    +"the top of the staff an azure sapphire is mounted in a silvery "
    +"dragon like claw.\n");
    
    set_hit(30);
    set_pen(35);
    set_wt(W_POLEARM); 
    set_dt(W_BLUDGEON); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,35));

    set_hands(W_BOTH); 
}
