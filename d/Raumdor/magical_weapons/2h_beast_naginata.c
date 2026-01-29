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
 *
 * Carnak: September 8th 2017.
 * - Added a prop to allow for altering the weapon to a hoopak.
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

inherit "/d/Raumdor/magical_weapons/2h_beast_weapon_base";

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

/*
 * Function name: create_2h_beast_weapon
 * Description  : Constructor to configure the weapon when it is created.
 */
public void
create_2h_beast_weapon()
{
    set_name("rust-red_long_naginata");
    add_name("naginata");
    add_name("polearm");
    set_adj("rust-red");
    add_adj("long");
          
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
      
    set_short("rust-red long naginata");
    
    set_long("This two-handed naginata has a long wooden pole clad in "
        +"green ropy but rugged leather held on with brass tacks. The " 
        +"blade is long and slightly curved, sharpened equally on both "
        +"sides. It's made of rust-red metal.\n");
        
    /* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
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
}


