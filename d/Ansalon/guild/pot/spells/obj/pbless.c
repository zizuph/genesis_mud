/* 
 * pbless object - blessed by the dark forces
 * (protection from good)
 * 2004-07-06   Cotillion
 *  Fixed runtime in hit_me
 */

#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

#define BLESS_SUBLOC "pot_bless_subloc"

int gLvl;   // Level of caster (used in damage reduction)

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("You feel the touch of the Queen of Darkness " +
    "leave you, and you are more vulnerable to the corrupted forces of " +
    "good.\n");
    
    spell_target->remove_subloc(BLESS_SUBLOC);
    
    remove_spell_effect_object();

    return 1;
}

public int
start()
{
    set_spell_effect_desc("protection from good");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    if (!shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    gLvl = spell_caster->query_priest_level();
    spell_target->add_subloc(BLESS_SUBLOC, TO);

    set_alarm(900.0, 0.0, dispel_spell_effect);

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != BLESS_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);
	
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are fortified by the power of the Dark Queen.\n";

    return C(HE(me)) + " is fortified by the power of Takhisis.\n";
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    mixed prop;
    int red = 0;

    if (living(attacker) && (attacker->query_alignment() > 500) &&
        (dt != MAGIC_DT))
    {
        object wep;
        
    	switch (gLvl)
    	{
    	    case 0:     /* 5 - 15 % */
    	        red = 5 + random(attacker->query_alignment() / 120);
    	        if (red > 15)
    	            red = 15;
    	        break;
    	    case 1:     /* 5 - 20 % */
    	        red = 5 + random(attacker->query_alignment() / 80);
    	        if (red > 20)
    	            red = 20;
    	        break;
    	    default:    /* 10 - 25 % */
    	        red = 10 + random(attacker->query_alignment() / 80);
    	        if (red > 25)
    	            red = 25;
    	}

    	red *= 100 - (attacker->query_stat(SS_DIS)/4);
        if (red < 0)
            red = 0;

        // Check for a magic weapon.
        wep = attacker->query_weapon(attack_id);
        if (objectp(wep) && wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
        {
            int pow;

            /* Let's not runtime on broken props */
            prop = wep->query_prop(MAGIC_AM_MAGIC);
            if (pointerp(prop) && sizeof(prop) >= 2)
                pow = prop[0];

            if (pow > spell_power)
            {
                // Magic weapon strikes completely through the blessing.
                return shadow_who->hit_me(wcpen, dt, attacker, attack_id);
            }
            
            // Still, a magic weapon offers some benefit against the protection
            red = (red * 2) / 3;
        }

    	wcpen -= wcpen * red / 10000;
    }

    return shadow_who->hit_me(wcpen,dt,attacker,attack_id);
}
