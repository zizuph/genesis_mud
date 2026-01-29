/*
 *  /d/Raumdor/magical_weapons/2h_undull_beast_mace.c
 *
 *   This two-handed weapon has a hit/pen of  
 *   58, and will not dull. It is rewarded by sacrificing a regular 
 *   variant in the flame at /d/Raumdor/common/temple/temple_join.c
 *
 *   Nerull,  25/8/2020.
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

inherit "std/weapon";

/*
 * Function name: create_2h_beast_weapon
 * Description  : Constructor to configure the weapon when it is created.
 */
public void
create_weapon()
{    
    set_name("rust_red_undull_spiked_mace");
	add_name("mace");
    add_name("club");
    set_adj("rust-red");
    add_adj("engraved");
    add_adj("warped");
          
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    
    set_hit(58);
    set_pen(58);
      
    set_short("warped rust-red spiked mace");
    
    set_long("This two-handed mace has a long wooden handle clad in green "
        +"ropy but rugged leather held on with brass tacks. The head is "
        +"an enormous ball made of rust-red metal, and has six solid " 
        +"spikes. At the base of the head you see a small " 
        +"etching of a skull and a scythe. The mace seems to be "
        +"warped by some unknown force.\n");
        
    add_item(({"etching"}), "Etched into the rust-red metal, you see a "
        +"decoration of an decayed grinning skull resting on a scythe.\n");
        
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(58, W_CLUB)); 
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "This weapon is warped by magical fire, making it denser than normal.\n", 5,
    "The " + short() + " will not dull by any ordinary means.\n", 50}));
                                 
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "This two-handed weapon has a hit/pen of " 
        +"58, and will not dull. It is rewarded by sacrificing a regular "
        +"variant in the flame at /d/Raumdor/common/temple/temple_join.c\n");     
    
    // Make it keepable by default.
    set_keep();
}


int set_dull(int du)
{
    return 0;
}