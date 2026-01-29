/*
 *  /d/Raumdor/magical_weapons/2h_beast_naginata.c
 *
 *  This is one of four two-handed weapons that the beastlord
 *  in Raumdor wields. It is magical and sporadically deals extra 
 *  damage to the target. 
 *
 *  The beastlord: /d/Raumdor/common/npc/blord.c
 *
 *  Nerull,  20/6-10.
 */ 
 
inherit "/std/weapon";
#include "/d/Raumdor/defs.h";
#include "/d/Raumdor/balance/magical_weaponry_stats.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <std.h>
#include <options.h>
#include <filter_funs.h>


/*
 * Function name: create_weapon
 * Description  : Constructor to configure the weapon when it is created.
 */
public void
create_weapon()
{
      
    set_name("naginata");
    add_name("polearm");
    set_adj("rust-red");
    add_adj("long");
          
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
      
    set_short("rust-red long naginata");
    
    set_long("This two-handed naginata has a long wooden pole clad in "
        +"green ropy but rugged leather held on with brass tacks. The " 
        +"blade is long and slightly curved, sharpened equally on both "
        +"sides. It's made of rust-red metal. An etching of a skull "
        +"and a scythe decorates the base of the blade on both sides.\n");
        
    add_item(({"etching"}), "Etched into the rust-red metal, you see a "
        +"decoration of an decayed grinning skull resting on a scythe.");

        
    set_hit(TWOH_BEAST_NAGINATA_HITPEN_DEFAULT);
    set_pen(TWOH_BEAST_NAGINATA_HITPEN_DEFAULT);

    set_hands(W_BOTH);
    set_wf(this_object());

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
    add_prop(OBJ_I_WEIGHT, 8000); /* 8 kilos. */
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "This naginata contains a trapped soul.\n", 5,
    "The trapped soul within will sporadically empower " +
    "the naginata and help dealing additional damage to the " +
    "enemy.\n", 50}));
                                 
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "This two-handed weapon has a hit/pen of " 
        +"58, and deals a damage proc, melee damage. The factors involved "
        +"in the strength of the combat special is found in "
        +"/d/Raumdor/balance/magical_misc_stats.h. "
        +"(TWOH_BEAST_NAGINATA_PROC) and "
        +"(TWOH_BEAST_NAGINATA_SPECIAL_MULTIPLIER).\n");
     
}


/* Masking wield() function*/
int
wield()
{    
    log_file("beast_weaponry_wielded", short()+" wielded at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");
    return 0;
}


/* Masking unwield() function*/
int
unwield()
{        
    log_file("beast_weaponry_dropped", short()+" dropped at " +extract(ctime(time())) + 
    " by "+capitalize(wielder->query_real_name())+".\n");
    
    return 0;
}


/*
 * Function name: did_hit
 * Description  : Special attack. What happens when the weapon hits 
 *                the target.
 * Arguments    : int aid, string hdesc, int phurt, object enemy, int dt,
 *                int phit, int dam.
 */
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,
int dam)
{
    int mindam;
    
    int did_hit_result = ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
          
          
    // If we miss, we miss.
    if (phurt < 0)  
    { 
        return did_hit_result;
    } 
    
   
    // The messages for the weapon.
    if(random(100) < TWOH_BEAST_NAGINATA_PROC)
    {
              
        wielder->catch_msg("As you impale "+QTNAME(enemy)+", a " 
            +"scintillating black energy ripples along the length of the "
            +"curved blade, forcing the "+short()+" to lacerate deeply into "
            +enemy->query_possessive()+" "+hdesc+", cutting bones and "
            +"severing arteries.\n");
        
        enemy->catch_msg("As "+QCTNAME(wielder)+" impales you, a " 
            +"scintillating black energy ripples along the length "
            +"of the "+short()+"'s curved blade, forcing it to lacerate "
            +"deeply into your "+hdesc+", cutting bones and " 
            +"severing arteries.\n");
        
        wielder->tell_watcher("As "+QCTNAME(wielder)+" impales "
            +QTNAME(enemy)+" with "+wielder->query_possessive()+" "
            +short()+", a scintillating black energy ripples along the "
            +"length of the curved blade, forcing it to lacerate deeply into "
            +enemy->query_possessive()+" "+hdesc+", cutting bones and " 
            +"severing arteries.\n",enemy);
 
        // The damage formula.
        mindam = TWOH_BEAST_NAGINATA_SPECIAL_MULTIPLIER * 
        ((dam * 30 / 100) + random(dam / 10));
        enemy->heal_hp(-mindam);
        
        return 1;
    }

    return did_hit_result;
}



