/*
 * A flower for WAYM_HOUSE_DIR + h_5_3
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>



	string adj1 = "perfect";
	 string adj2 = "red";
	 string name = "rose";
	 
 void
 create_object()
 {
	
	 set_name(name);
	 add_name("kitchen_rose");
	 add_name("flower");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short("@@my_short@@");
	 
	 set_long("@@my_long@@");

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
 
string
 my_short()
 {
	 return(adj1 + " " + adj2 + " " + name);
 }
 
 string
 my_long()
 {
	 
		 return("This " + my_short() + " is a great example of what a "
		+ "rose can be. Its stem is long and straight and has been trimmed "
		+ "of any thorns. The flower is open perfectly and shows no sign "
		+ "of wilting. In all honesty, you have never seen a redder rose "
		+ "than this one. It's beautiful.\n");
	
 }
 
