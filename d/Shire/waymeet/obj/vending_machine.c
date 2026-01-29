/*
 * A button
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

object obj;

 void
 create_object()
 {
	 string adj1 = "tall";
	 string adj2 = "black";
	 string name = "box";
	 
	 set_name(name);
	 add_name("machine");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("vending");
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	 set_long("This " + query_short() + " looks like a vending "
		+ "machine. It clearly has no place in these realms and "
		+ "must have dropped in through a dimentional rift from the "
		+ "nether. It's a bit over two meters high, and about a "
		+ "meter wide and deep. There are pictures on the front "
		+ "of it, as well as buttons.\nYou get the sense this "
		+ "vending machine appeared here as a way to help wizards "
		+ "test the quest from Imbert!\n");
	add_item( ({"picture", "pictures"}), "You see pictures of "
		+ "an ogee, a lyne arm, a joint, a copper nozzle, and "
		+ "a cone.\n");
	add_item( ({"button", "buttons"}), "You see a button in the "
		+ "shape of each of the pictures. There is an ogee "
		+ "button, a lyne arm button, a joint button, a nozzle "
		+ "button, and a cone button. You could likely <press> "
		+ "one of the buttons.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 10000);
	add_prop(OBJ_I_WEIGHT, 20000);
	add_prop(OBJ_I_VALUE, 1);
	add_prop(OBJ_M_NO_GET, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("do_press", "press");
	 add_action("do_press", "push");
 }
 
 void
 deliver_item()
 {
	 tell_room(environment(TP),
			"The " + query_short() + " shakes and rattles a bit.\n");
		 
		 obj->move(TP);
		 write("You reach out and take an " + obj->query_short()
			+ " from the " + query_short() + ".\n");
		say(QCTNAME(TP) + " reaches out and takes an " + obj->query_short()
			+ " from the " + query_short() + ".\n");
 }
 
 int
 do_press(string str)
 {
	
	 if(str == "ogee" | str == "ogee button")
	 {
		  obj = clone_object(WAYM_OBJ_DIR + "still_pipe_1");
		  deliver_item();
		return 1;
	 }
	 if(str == "lyne" | str == "lyne arm" | str == "lyne button" | str == "lyne arm button")
	 {
		obj = clone_object(WAYM_OBJ_DIR + "still_pipe_2");
		  deliver_item();
		return 1; 
	 }
	 if(str == "joint" | str == "pipe joint")
	 {
		 obj = clone_object(WAYM_OBJ_DIR + "still_pipe_3");
		  deliver_item();
		return 1;
	 }
	 if(str == "cone" | str == "cone button")
	 {
		 obj = clone_object(WAYM_OBJ_DIR + "chandelier_cone");
		  deliver_item();
		return 1;
	 }
	 if( str == "nozzle" | str == "nozzle button")
	 {
		 obj = clone_object(WAYM_OBJ_DIR + "still_nozzle");
		  deliver_item();
		return 1;
	 }
	 else
	 {
		 notify_fail("Press which button?\n");
		 return 0;
	 }
 }
 