/*
 * A paint chip
 * (for no good reason whatsoever)
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
	 set_name("chip");
	 add_name("paint");
	 set_adj("paint");
	 add_adj("red");
	 
	 set_short("red paint chip");
	 
	 set_long("This is a bit of red paint that chipped off of something. "
		+ "This type of chipping commonly happens when someone knocks too "
		+ "agressively on a door.\n");


	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_VALUE, 0);
 }
 
 void
 init()
 {
	 ::init();

 }
 
