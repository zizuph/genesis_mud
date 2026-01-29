inherit "/d/Avenir/inherit/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_weapon()
{
	::create_weapon();
	set_name("sword");    
	add_name("stick");
	set_short("a small stick");
	 
	set_hit(20);
	set_pen(20);

	set_wt(W_SWORD);
	set_dt(W_SLASH);

        add_prop(OBJ_I_VALUE, 400);
	add_prop(OBJ_I_WEIGHT, 800); 
	add_prop(OBJ_I_VOLUME, 1000);
}

