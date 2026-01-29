/*
 *  /d/Raumdor/magical_weapons/2h_beast_broadsword.c
 *
 *  This is one of four two-handed weapons that the beastlord
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

inherit "/d/Raumdor/magical_weapons/2h_beast_weapon_base";

/*
 * Function name: create_2h_beast_weapon
 * Description  : Constructor to configure the weapon when it is created.
 */
public void
create_2h_beast_weapon()
{      
    set_name("rust-red_engraved_broadsword");
    add_name("broadsword");
    add_name("sword");
    set_adj("rust-red");
    add_adj("engraved");
          
    set_wt(W_SWORD);
    set_dt(W_SLASH);
      
    set_short("rust-red engraved broadsword");
    
    set_long("This two-handed sword has a long grip clad in green ropy "
        +"leather, and the guard is a crescent moon of black steel. The "
        +"pommel is a black onyx of nearly two inches in " 
        +"diameter, irremovable from the weapon. The blade is broad and "
        +"made of a rust-red metal.\n");
        
    add_item(({"engraving"}), "Engraved into the surface of the blade on "
        +"both sides, you see a long-stretched decoration of a horned "
        +"devil.\n");
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
