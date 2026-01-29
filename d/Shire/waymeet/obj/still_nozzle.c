/*
 * A nozzle for the quest in the 
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
	 string adj1 = "small";
	 string adj2 = "copper";
	 string name = "nozzle";
	 

	 set_name("_still_quest_5");
	
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj2);
	
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " looks like it would be used "
		+ "to run liquid from a pot still into a container. It'd be "
		+ "pretty useful if you ran a distillery!\n");
		

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VALUE, 100);
	add_prop(OBJ_M_NO_BUY, 1);
 }
 
 void
 init()
 {
	 ::init();
 }
 