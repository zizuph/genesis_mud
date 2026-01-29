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
	 string adj1 = "copper";
	 string adj2 = "pipe";
	 string name = "joint";
	 

	 set_name("_still_quest_4");
	 add_name("pipe");
	 add_name("joint");
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj2);
	 add_adj("nut");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " looks like it would be used "
		+ "to fit two pipes together. It's quite small, perhaps as long "
		+ "as a hobbit's finger, but as big around as two or three "
		+ "together.\n");
		

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
 