inherit "/std/armour";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/stdproperties.h" /* The properties of value, volume and weight */
#include <macros.h>
public void
create_armour()
{
	set_name("bracers");
	set_adj("studded");
	add_adj(({"leather"}));
	set_short("studded leather bracers");
	set_long("These are studded leather bracers, with "
		+"red studs on a black background. These bracers "
		+"appear very durable and seem to offer "
	    +"ample protection to the wearer.\n");
	
	set_at(A_ARMS);

    set_ac(5 + random(2));
    set_am(({0, 0, 0}));
    
}