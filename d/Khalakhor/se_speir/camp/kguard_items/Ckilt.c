inherit "/std/armour";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/stdproperties.h" /* The properties of value, volume and weight */
#include <macros.h>
public void
create_armour()
{
	set_name("kilt");
	set_adj("studded");
	add_adj(({"leather"}));
	set_short("studded leather kilt");
	set_long("This is a studded leather kilt, with "
		+"red studs on a black background. This kilt "
		+"appears to offer ample protection and "
	    +"a long lasting value to the wearer.\n");
	
	set_at(A_TORSO);

    set_ac(15 + random(2));
    set_am(({0, 0, 0}));
    
}