inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

create_armour()
{
	set_short("barbed black leather armour");
	set_long("This wicked leather armour is covered with myriads of"
		+" sharp barbs made to catch hold of an enemy's weapon and"
		+" throw him off beat. The armour is stuffed with wool to make it"
		+" rather comfortable, despite the barbs.\n");
		
	set_name("leather armour");
	set_adj("barbed"); add_adj("black");
	add_name("leather");
	add_name("armour");
	
	set_at(W_BODY);
	set_ac(15);
	
	add_prop(OBJ_S_WIZINFO, "This armour is bought at the Cult of"
		+" Melkor guild home at a low rate. Its fairly good as far"
		+" as leather armours go, but has no special properties.\n");
	add_prop(OBJ_I_NO_SELL, 1 );
}
