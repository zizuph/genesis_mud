/*
 * A chandelier cone for the quest in the 
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
	 string name = "cone";
	 

	 set_name("_still_quest_1");
	 add_name("chandelier_cone");
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj2);
	 add_adj("nut");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " is about as wide as a drain pipe "
		+ "on top and as wide as a large pot on the bottom. It has a curvy "
		+ "yet undeniably conical shape and is very very shiny. You see "
		+ "some bolt holes in the top, which could be used to attach it "
		+ "to a pipe or some such thing.\n");
		
	add_item( ({"hole", "bolt hole", "bolt holes"}),
		"These holes are about the size of a human's little finger. They "
		+ "look to be about the same size as a bolt would be.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_I_WEIGHT, 20000);
	add_prop(OBJ_I_VALUE, 500);
 }
 
 void
 init()
 {
	 ::init();
 }
 