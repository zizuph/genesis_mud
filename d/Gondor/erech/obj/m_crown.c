inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour()
{
    set_name(({"crown","helm"}));
    set_adj("tarished");
    set_long("This was the royal crown in a realm fallen long ago, " +
	"the last king who wore it are bound to the oath of Isildur.\n");
    set_default_armour(5, A_HEAD, (({ 0, 0, 0})), 0);	    
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 600); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(400)-100);
}  
