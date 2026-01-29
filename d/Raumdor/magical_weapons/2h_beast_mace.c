/*
 *  /d/Raumdor/magical_weapons/2h_beast_mace.c
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
      
    set_name("rust_red_spiked_mace");
	add_name("mace");
    add_name("club");
    set_adj("rust-red");
    add_adj("engraved");
          
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
      
    set_short("rust-red spiked mace");
    
    set_long("This two-handed mace has a long wooden handle clad in green "
        +"ropy but rugged leather held on with brass tacks. The head is "
        +"an enormous ball made of rust-red metal, and has six solid " 
        +"spikes. At the base of the head you see a small " 
        +"etching of a skull and a scythe.\n");
        
    add_item(({"etching"}), "Etched into the rust-red metal, you see a "
        +"decoration of an decayed grinning skull resting on a scythe.\n");
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
    wielder->catch_msg("As you smash "+QTNAME(enemy)+", a " 
        +"scintillating black energy ripples up the solid spikes "
        +"on the head, forcing the "+short()+" to pummel deeply into "
        +enemy->query_possessive()+" "+hdesc+", crushing bones and "
        +"mutilating flesh.\n");
    
    enemy->catch_msg("As "+QCTNAME(wielder)+" smashes you, a " 
        +"scintillating black energy ripples up the solid spikes "
        +"on the "+short()+"'s head, forcing it to pummel "
        +"deeply into your "+hdesc+", crushing bones and mutilating " 
        +"flesh.\n");
    
    wielder->tell_watcher("As "+QCTNAME(wielder)+" smashes "
        +QTNAME(enemy)+" with "+wielder->query_possessive()+" "
        +short()+", a scintillating black energy ripples up the "
        +"solid spikes on its head, forcing it to pummel deeply into "
        +enemy->query_possessive()+" "+hdesc+", crushing bones and " 
        +"mutilating flesh.\n",enemy);
}


