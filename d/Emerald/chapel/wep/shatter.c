/* chapel/wep/shatter.c is cloned by chapel/npc/usher.c */
inherit "/std/weapon";
 
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
 
create_weapon()
{
    set_name("sword");
    set_short("shatter sword");
    set_long("This sword is made of crystal and while "+
       "it appears to be fragile, it is not.  It is razor sharp and "+
       "rather light.\n");
    set_adj("shatter");
 
    set_default_weapon(15, 20, W_SWORD, W_SLASH | W_IMPALE,
         W_NONE,  0);
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME,  560);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15, 20) + random(130) - 65);
}
