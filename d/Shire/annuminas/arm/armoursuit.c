inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name(({"armour", "armour-suit", "suit","_numenorean_treasure_"}));
    set_short("golden suit of armour");
    set_adj(({"golden","gold","numenorean", "suit"}));
    set_long("This is a magnificent work of ancient craftsmanship!\n"+
    "Made in Numenor in ages long ago, it is of make and quality of "+
    "gold that never has been seen in Middle Earth since the Fall of "+
    "Numenor.\n");
	
    set_ac(40);
    set_at(A_BODY | A_ARMS | A_LEGS);
    
    add_prop(OBJ_I_WEIGHT, 35000);
    add_prop(OBJ_I_VALUE, 200*12*12);
    add_prop(OBJ_I_VOLUME, 10000);
}
