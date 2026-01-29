/*
 *  /d/Raumdor/magical_weapons/2h_beast_cleaver.c
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
      
    set_name("rust_red_heavy_cleaver");
	add_name("cleaver");
    add_name("axe");
    set_adj("rust-red");
    add_adj("wicked");
          
    set_wt(W_AXE);
    set_dt(W_SLASH);
      
    set_short("rust-red heavy cleaver");
    
    set_long("This two-handed cleaver has a long wooden handle clad in "
        +"green ropy but rugged leather held on with brass tacks. The " 
        +"head is very broad with a single long jagged edge, and it is "
        +"made of rust-red metal. The eye of the cleaver resembles a " 
        +"skull and a scythe.\n");
        
    add_item(({"eye"}), "On the top of the cleaver where the blade wraps "
        +"around the handle, you see a carving resembling an decayed " 
        +"grinning skull resting on a scythe.\n");
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
    wielder->catch_msg("As you cut "+QTNAME(enemy)+", a " 
        +"scintillating black energy ripples along the length of the "
        +"heavy blade, forcing the "+short()+" to burrow deeply into "
        +enemy->query_possessive()+" "+hdesc+", cutting bones and "
        +"sending sinewy flesh and blood flying everywhere.\n");
    
    enemy->catch_msg("As "+QCTNAME(wielder)+" cuts you, a " 
        +"scintillating black energy ripples along the length "
        +"of the "+short()+"'s heavy blade, forcing it to burrow "
        +"deeply into your "+hdesc+", cutting bones and sending "
        +"sinewy flesh and blood flying everywhere.\n");
    
    wielder->tell_watcher("As "+QCTNAME(wielder)+" cuts "
        +QTNAME(enemy)+" with "+wielder->query_possessive()+" "
        +short()+", a scintillating black energy ripples along the "
        +"length of the heavy blade, forcing it to burrow deeply into "
        +enemy->query_possessive()+" "+hdesc+", cutting bones and " 
        +"sending sinewy flesh and blood flying everywhere.\n",enemy);
}


