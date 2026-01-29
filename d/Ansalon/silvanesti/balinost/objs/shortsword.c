#pragma save_binary

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"


/*
 * Function name: reset_weapon
 * Description:   Reset the weapon
 * Arguments:	  arg: The reset argument.
 */
nomask
create_weapon()
{
          set_name("shortsword");
          set_short("silver-bladed shortsword");
          set_long("The blade of this shortsword is made of silver and "+
            "is commonly used by Silvanesti guards.  The sword is light "+
            "wieght and very sharp at its tip.\n");
	  set_hit(15);
	  set_pen(15);
	  set_wt(W_SWORD);
	  set_dt(W_SLASH);
	  set_hands(W_NONE);
          set_pshort("silver-bladed shortswords");
          set_pname("shortswords");
          add_name("sword");
          add_pname("swords");
          set_adj("silver-bladed");
}

/*
 * Function name: 
 * Description:   
 * Arguments:	  
 * Returns:       
 */
