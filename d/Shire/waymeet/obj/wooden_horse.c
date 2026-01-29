/*
 * A wooden horse toy
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
	 set_name("toy");
	 add_name("horse");
	 set_adj("wooden");
	 add_adj("rough");
	 add_adj("worn");
	 set_short("rough wooden horse");
	 
	 set_long("This horse looks hand carved. Looking closely you can see "
		+ "the knife-strokes and cut marks. Parts of the horse also look "
		+ "very worn, like the area around the saddle where a boy might "
		+ "use a pinch grip to move the toy around.\n");

	add_item("saddle", "The saddle is carved out of the same piece of wood "
		+ "as the horse, but it looks smooth and worn. Someone has been "
		+ "holding the horse here and playing with it!\n");
	add_item( ({"knife strokes", "strokes", "marks", "cut marks"}),
		"The knife strokes are uneven and vary in depth. Whoever carved this "
		+ "horse was not very good at woodworking. Likely they carved "
		+ "the horse out of love.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VALUE, 1);
 }
 
 void
 init()
 {
	 ::init();

 }
 

string query_recover() 
{ 
    return MASTER + ":"; 
}
