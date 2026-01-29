/*
 * Vomit
 * For players who have a little too much to drink in 
 * The Foaming Mug in Waymeet
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
	 string adj1 = "puddle";
	 string adj2 = "yellowish";
	 string name = "vomit";
	 
	 set_name("_drunk_person_vomit");
	 add_name("throw up");
	 add_name("puddle");
	 add_name(name);
	 set_adj(adj1);
	 add_adj(adj1);
	
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " is pretty nasty. It's a pretty "
		+ "big puddle, the kind people leave after a night of heavy drinking. "
		+ "It smells awful... really awful... and it has ... chunks.. in it. "
		+ "Gross.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_M_NO_GET, 1);
 }
 
 void
 init()
 {
	 ::init();
 }
 