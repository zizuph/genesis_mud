/*
 * A button
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
	 string adj1 = "small";
	 string adj2 = "blue";
	 string name = "button";
	 
	 set_name(name);
	 set_adj(adj1);
	 add_adj(adj1);
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " looks like it fell off of a doll, "
		+ "or maybe a child's vest. It's certainly not large enough for use "
		+ "on an adult's clothing. The button is a beautiful shade of blue "
		+ "and looks as if it's seen almost no use.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_VALUE, 1);
 }
 
 void
 init()
 {
	 ::init();
 }
 