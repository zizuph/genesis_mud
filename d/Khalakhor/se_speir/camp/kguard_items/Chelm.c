inherit "/std/armour";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/stdproperties.h" /* The properties of value, volume and weight */
#include <macros.h>
public void
create_armour()
{
	set_name("cap");
	set_adj("hard");
	add_adj(({"leather"}));
	set_short("hard leather cap");
	set_long("This is a hard leather cap, checkered black "
		+"and red, with the clan's insignia, the Quaternary "
		+"Celtic Knot, pinned on the sides. The cap looks "
		+"very durable and offer ample protection in combat.\n");
	
	set_at(A_HEAD);

    set_ac(5 + random(2));
    set_am(({0, 0, 0}));
    
}