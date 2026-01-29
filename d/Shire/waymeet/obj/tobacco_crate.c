/*
 * A crate of tobacco
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>


 void
 create_object()
 {
	 string adj1 = "wooden";
	 string adj2 = "tobacco";
	 string name = "crate";
	 
	 set_name(name);
	 add_name("_pipeweed_crate_");
	 add_name("pipeweed");
	 add_name("weed");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("pipeweed");
	 add_adj("pipe");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " has the words 'Old Toby' stenciled "
		+ "on the side. It's clearly a crate of some of the finest Pipeweed "
		+ "you can buy in the Shire!\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10000);
	add_prop(OBJ_I_WEIGHT, 20000);
	add_prop(OBJ_I_VALUE, 200000);
	add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_M_NO_STEAL, 1);
 }
 
 void
 init()
 {
	 ::init();
 }
 