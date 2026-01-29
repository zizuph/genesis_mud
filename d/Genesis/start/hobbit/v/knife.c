#pragma save_binary

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("curved");
    set_short("curved knife");
    set_pshort("curved knives");
    set_long("The curved knife looks like it once belonged to an orc.\n");
    set_default_weapon(
		       random(5)+3,         /* Weapon hit         */
		       random(10) + 6,      /* Weapon penetration */
		       W_KNIFE,             /* Weapon type        */
		       W_IMPALE | W_SLASH,  /* Damage type        */
		       W_NONE,              /* Used hands         */
		       0);
    
    add_prop(OBJ_I_WEIGHT,560 + random(200));
    add_prop(OBJ_I_VOLUME,400 + random(170));
    add_prop(OBJ_I_VALUE,8 + random(10));
}    