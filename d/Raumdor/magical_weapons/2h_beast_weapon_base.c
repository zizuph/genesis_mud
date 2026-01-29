/*
 *  /d/Raumdor/magical_weapons/2h_beast_weapon_base.c
 *
 *  This is the base two-handed weapon that the beastlord
 *  in Raumdor wields. It is magical and sporadically deals extra 
 *  damage to the target. 
 *
 *  The beastlord: /d/Raumdor/common/npc/blord.c
 *
 *  Nerull,  20/6-10.
 */ 
 
#include "/d/Raumdor/defs.h";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <std.h>
#include <options.h>
#include <filter_funs.h>

inherit "/d/Genesis/specials/resist";
inherit "/std/weapon";

// Defines
#define TWOH_BEAST_SPECIAL_MULTIPLIER       5
#define TWOH_BEAST_PROC                     20
#define LAST_SPECIAL_HIT                    "_last_special_hit"
#define TWOH_BEAST_HIT_DEFAULT              58
#define TWOH_BEAST_PEN_DEFAULT              58

/*
 * Function:    create_2h_beast_weapon
 * Description: This is the default create function for each inheriting
 *              beast weapon.
 */
public void
create_2h_beast_weapon()
{
    // Mask this in each specific beast weapon
    set_short("rust-red base weapon");
    
    set_long("You should never see this weapon.\n");    
}

/*
 * Function name: create_weapon
 * Description  : Constructor to configure the weapon when it is created. This
 *                is set to nomask so that the parameters inside cannot be
 *                changed by the inheriting weapon. Petros (AoB) - 10/3/2010
 */
public nomask void
create_weapon()
{
    create_2h_beast_weapon();
    
    set_hit(TWOH_BEAST_HIT_DEFAULT);
    set_pen(TWOH_BEAST_PEN_DEFAULT);

    set_hands(W_BOTH);
    set_wf(this_object());
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
    add_prop(OBJ_I_WEIGHT, 8000); /* 8 kilos. */
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "This weapon contains a trapped soul.\n", 5,
    "The trapped soul within will sporadically empower " +
    "the " + short() + " and assist the wielder against their " +
    "enemy.\n", 50}));
                                 
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "This two-handed weapon has a hit/pen of " 
        +"58, and deals a damage proc, melee damage.\n");     
}


/* Masking wield() function*/
public mixed
wield(object obj)
{    
    log_file("beast_weaponry_wielded", short()+" wielded at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");

    return 0;
}


/* Masking unwield() function*/
public mixed
unwield(object obj)
{        
    log_file("beast_weaponry_unwielded", short()+" unwielded at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");
    
    return 0;
}


/* Masking enter_env*/
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
        
    log_file("beast_weaponry_taken", short()+" picked up at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");
}


/*Maskong leave_env*/
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
        
    log_file("beast_weaponry_dropped", short()+" dropped at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");    
}



/* 
 * Function:    do_describe_extra_damage
 * Description: This function should be masked by each weapon that wishes to
 *              customize the damage description for the extra damage.
 *              All the necessary info should be available in the arguments,
 *              which are identical to did_hit, except for an extra argument
 *              to pass the actual extra damage that was done.
 */
public void
do_describe_extra_damage(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam, int extra_dam)
{
    wielder->catch_msg("As you strike "+QTNAME(enemy)+", a " 
        +"scintillating black energy ripples up the edge of the "
        +"blade, forcing the "+short()+" to penetrate deeply into "
        +enemy->query_possessive()+" "+hdesc+", sending sinewy "
        +"flesh and blood flying everywhere.\n");
    
    enemy->catch_msg("As "+QCTNAME(wielder)+" strikes you, a " 
        +"scintillating black energy ripples up the edge of "
        +"the "+short()+"'s blade, forcing it to penetrate "
        +"deeply into your "+hdesc+", sending sinewy flesh "
        +"and blood flying everywhere.\n");
    
    wielder->tell_watcher("As "+QCTNAME(wielder)+" strikes "
        +QTNAME(enemy)+" with "+wielder->query_possessive()+" "
        +short()+", a scintillating black energy ripples up the "
        +"edge of its blade, forcing it to penetrate deeply into "
        +enemy->query_possessive()+" "+hdesc+", sending sinewy flesh "
        +"and blood flying everywhere.\n",enemy); 
}

/*
 * Function name: did_hit
 * Description  : Special attack. What happens when the weapon hits 
 *                the target.
 * Arguments    : int aid, string hdesc, int phurt, object enemy, int dt,
 *                int phit, int dam.
 */
public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int extra_damage = 0;
    
    int did_hit_result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
                   
    // If we miss, we miss.
    if (phurt < 0 || dam == 0)  
    { 
        return did_hit_result;
    } 
       
    if (query_prop(LAST_SPECIAL_HIT) + 5 > time())
    {
        // We limit the special attack to once every 5 seconds
        return did_hit_result;
    }
    
    // This weapon has a percentage chance of doling out extra damage.
    if (random(100) < TWOH_BEAST_PROC)
    {
        add_prop(LAST_SPECIAL_HIT, time());
        // The damage formula gives an extra 15-25% damage
        extra_damage = TWOH_BEAST_SPECIAL_MULTIPLIER * ((dam * 15 / 100) + random(dam / 10));
        // This damage is magical by nature, so we need to do some resistance checks
        int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_DEATH }));
        extra_damage = extra_damage - ((extra_damage * resistance) / 100);
        enemy->heal_hp(-extra_damage);
        do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam, extra_damage);              
    }

    return did_hit_result;
}



