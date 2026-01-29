inherit "/std/armour";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/stdproperties.h" /* The properties of value, volume and weight */
#include <macros.h>
public void
create_armour()
{
	set_name("greaves");
	set_adj("studded");
	add_adj(({"leather"}));
	set_short("studded leather greaves");
	set_long("These are studded leather greaves, with "
		+"red studs on a black background. These greaves "
		+"appear very durable and seem to offer "
	    +"ample protection to the wearer.\n");
	
	set_at(A_LEGS);

    set_ac(5 + random(2));
    set_am(({0, 0, 0}));
    
}