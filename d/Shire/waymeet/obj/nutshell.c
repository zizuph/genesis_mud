/*
 * A nut shell
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
	 string adj1 = "cracked";
	 string adj2 = "walnut";
	 string name = "shell";
	 
	 set_name(name);
	 add_name("nutshell");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("nut");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " has been used and discarded. It "
		+ "used to contain a walnut inside of it, which is a delicious thing "
		+ "to eat indeed. But the walnut has been eaten and the shell "
		+ "is all that's left. Now this shell is worthless, because, "
		+ "well, in a nutshell, it's empty.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_VALUE, 0);
 }
 
 void
 init()
 {
	 ::init();
 }
 