/* just a standard torch */
/* This object is put in bree/shop_store every reset */
/*  Made this torch keepable -Igneous */

inherit "/std/torch";
inherit "/lib/keep";
#include <stdproperties.h>

void
create_torch() {
   
	set_value(55 + random(40));
	set_strength(1);
	set_time(900);	
	set_name(({"torch", "shoptorch"}));   /* extra unique name */
	set_pname("torches");
	set_short("small torch");
	set_pshort("small torches");
	set_adj("small");
	set_long("@@torch_long");
	add_prop(OBJ_I_LIGHT,0);
	add_prop(OBJ_I_WEIGHT, 700);
	add_prop(OBJ_I_VOLUME, 1000);
}

string
torch_long() 
{
   return "It is a very simple looking torch.\n";
}

