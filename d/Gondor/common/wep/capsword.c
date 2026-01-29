/* The longsword of a captain of the army of Harad */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>
#include "/d/Gondor/defs.h"

create_weapon() 
{
    set_name(({"sword","haradrim longsword","weapon","longsword"}));
    set_long(BSN("A sharp haradrim longsword. The blade is made of " +
	"steel and decorated with gold ornaments."));
    set_short("haradrim longsword");
    set_pname("swords");
    add_pname("longswords");
    set_pshort("haradrim longswords");
    set_adj("haradrim");
    add_adj("long");
    add_adj("ornamented");
    add_adj("steel");
    set_default_weapon(27, 31, W_SWORD, (W_IMPALE|W_BLUDGEON), W_RIGHT, 0);
    add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(27, W_SWORD) - 100 + random(200)));        	        	 	  	
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(27, 31) + random(250) - 100));
}
