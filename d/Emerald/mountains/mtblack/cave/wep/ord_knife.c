/* A large hunting knife - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/mon/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
			       
public void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    add_pname("weapons");
    set_short("ordinary knife");
    set_pshort("ordinary knives"); 
    set_adj(({"ordinary","crude"}));
    set_long("It's a very basic knife, and there is nothing "  
	+ "special about it.  You could use it as a weapon, but it looks " 
	+ "like it was designed as a crude eating implement.\n");

    set_pen(10);
    set_hit(5);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT,  500);
    add_prop(OBJ_I_VOLUME,  100);
}
