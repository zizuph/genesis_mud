/*
 * A pipe for the quest in the 
 * Foaming Mug Inn 
 * /d/Shire/eastroad/western/foam_mug
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
	 string adj1 = "shiny";
	 string adj2 = "copper";
	 string name = "ogee";
	 

	 set_name("_still_quest_2");
	 add_name("pipe");
	 add_name("onion");
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj2);
	 add_adj("nut");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " looks a bit like a copper "
		+ "onion (although just a bit). The bottom of it looks just "
		+ "wide enough to fit into a hole for a large pipe, and then "
		+ "it expands outward into a small onion-shaped bulb, before "
		+ "it narrows to a hole about the width of a pipe.\n");
		

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_I_WEIGHT, 10000);
	add_prop(OBJ_I_VALUE, 500);
	add_prop(OBJ_M_NO_BUY, 1);
 }
 
 void
 init()
 {
	 ::init();
 }
 