/* This is the spell obj that is used by the fortify spell
 *        to give the knight an ac of 6 over his body
 *    created by percy.*/

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_armour()
{
    set_name("shieldobj");
    set_adj("magic");
    set_no_show();
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    set_default_armour(6, A_MAGIC);
}

void
set_duration(int dur) 
{ 
    set_alarm(itof(dur),0.0,"remove_object"); 
}

void
remove_object() 
{
    write("You feel Paladine's protection disappear.\n");
    this_player()->remove_arm(this_object());
    ::remove_object();
    return;
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

/* This shield is not recoverable. /Rastlin */
public string
query_recover()
{
    return 0;
}

