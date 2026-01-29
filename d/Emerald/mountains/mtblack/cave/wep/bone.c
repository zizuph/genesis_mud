/* A large bone - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/caveman.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
			       
public void
create_weapon()
{
    set_name("bone");
    add_pname("bones");
    add_pname("weapons");
    set_adj("large");
    set_short("large bone");
    set_pshort("large bones"); 
    set_long("It's large bone, that would make an effective club.\n" 
	+ "You're not quite sure where this bone came from, but judging by " 
	+ "the size, it was a pretty big creature.  At least you can rest "  
	+ "assured that the owner one this one must be quite dead...\n");

    set_hit(16);
    set_pen(8);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3000);
}
