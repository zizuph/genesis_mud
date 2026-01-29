/*
 * A pen for the scribe in Waymeet
 *
 * Raymundo, Feb 2020
 */
 
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <wa_types.h>
 
 inherit "/std/object";
 inherit "/lib/holdable_item";
 inherit "/lib/keep";

 
 public void
 create_object()
 {
	 set_name("pen");
	 add_adj( ({"white", "quill", "goose", "feather"}) );
	 set_short("white quill pen");
	 set_long("This is a pen made from a goose's tailfeather. The "
		+ "tip of the pen has been painstakingly carved, probably with "
		+ "a small knife, to a point. The tip is stained black with "
		+ "ink.\n");
		
	add_prop(OBJ_I_WEIGHT, 20);
	add_prop(OBJ_I_VOLUME, 20);
	add_prop(OBJ_I_VALUE, 1);
	
	set_slots(W_ANYH);
	set_keep(0);
 }
 
 void
 leave_env(object env, object to)
 {
	 ::leave_env(env, to);
	 holdable_item_leave_env(env, to);
 }
 
 string
 query_recover()
 {
	 return MASTER;
 }