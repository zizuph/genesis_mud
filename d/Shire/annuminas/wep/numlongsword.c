inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"longsword", "long sword","sword","_numenorean_treasure_"}));
    set_short("golden runed longsword");
    set_adj(({"bright","bright","runed", "numenorean"}));
    set_long("This bright golden longsword is covered in runes, which "+
     "have been faded by the years since it was forged to look like fine "+
     "scratches.  It is a majestic weapon and speaks of times gone by, "+
     "just by the reflection of the light.\n");
	
     set_default_weapon(25, 36, W_SWORD, W_SLASH, W_ANYH,this_object());
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 15*12*12);
    add_prop(OBJ_I_VOLUME, 1000);
}
