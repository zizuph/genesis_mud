/* This is the spell obj that is used by the fortify spell
 *        to give the knight an ac of 6 over his body
 *    created by percy.
 * adapted to the new spell system by Aridor, 10/95
 */
#include "../../guild.h"
#include "../local.h"

inherit "/std/armour";
inherit MAGIC_OBJECT;

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
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    set_default_armour(1, A_MAGIC);
}

void
init_spell(object caster, object target, object prev)
{
    
    set_default_armour(query_power() / 22 + 3, A_MAGIC);
    query_me()->wear_arm(this_object());
    find_living("aridor")->catch_msg("FORTIFY P:" + (query_power()/22+3) + " D:" +
				     query_duration() + ".\n");
}

void
remove_object() 
{
    query_me()->catch_msg("You feel Paladine's protection disappear.\n");
    query_me()->remove_arm(this_object());
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

