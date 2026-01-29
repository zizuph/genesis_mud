/*
 * A firework
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
int stick = 1;
int x = 0;
 void
 create_object()
 {
	 string adj1 = "red";
	 string adj2 = "tube";
	 string name = "firecracker";
	 
	 set_name(name);
	 add_name("firework");
	 set_adj(adj1);
	 add_adj(adj1);
	 add_adj("stick");
	 add_adj("on");
	 add_adj("a");
	 
	 set_short("red tube on a stick");
	 
	set_long("This " + query_short() + " is just a fat red tube glued onto "
		+ "a thin brown stick. There is a fuse coming out of the tube. "
		+ "You could light the " + name + ".\n");
	add_item("fuse", "There is a small piece of rolled paper sticking out of "
		+ "the bottom of the " + name + ". It looks like the type of thing "
		+ "you'd light.\n");
	add_item( ({"tube", "red tube"}), "The red tube is about the size of "
		+ "a goblin's nose-picking finger.\n");
	add_item("stick", "@@exa_stick@@");
	add_item( ({"tip", "fat tip", "rainbow tip", "fat rainbow tip"}),
		"The tip looks like an arrow head, but its over a finger wide. "
		+ "It has red, orange, yell, blue, and violet stripes on it, "
		+ "making it rainbow colored.\n");
	add_cmd_item( ({"fuse", name, "firecracker", "firework"}), "light", "@@do_light@@");
	add_cmd_item( ({"firework", "firecracker", "stick"}), "break", "@@do_break@@");
	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_WEIGHT, 300);
	add_prop(OBJ_I_VALUE, (1760 * 5));
	add_prop(OBJ_M_NO_SELL, 1);
 }
 
 void
 init()
 {
	 ::init();
	 
 }
 
 string
 exa_stick()
 {
	 if(stick == 1)
	 {
		 return("The stick is thin and brown, but perfectly straight. "
		 + "If you're not careful, you could break it.\n");
	 }
	 else
	 {
		 return("The stick is thin and brown. It has been broken.\n");
	 }
 }
 
 int
 do_break()
 {
	 if(stick == 0)
	 {
		 write("The stick is already broken!\n");
		 return 1;
	 }
	 write("You break the stick on the " + query_short() + ".\n");
	 say(QCTNAME(TP) + " breaks the stick on the " + query_short() + ".\n");
	 stick = 0;
	 return 1;
 }
 
 mixed
 do_light()
 {
	 if(environment(TP)->query_prop(ROOM_I_INSIDE) && x == 0)
	 {
		 write("You'll need to light the " + query_short()
			+ " outside!\n");
		return 1;
	 }
	 if(stick == 0)
	 {
		 write("The stick is broken! The firecracker won't work!\n");
		 return 1;
	 }
	switch(x)
	{
		case 0:
		TO->move(environment(TP));
		TO->add_prop(OBJ_M_NO_GET, 1);
		tell_room(environment(TO), QCTNAME(TP) + " sets the firework on the "
			+ "ground and lights the fuse. It begins to fizzle and then burns "
			+ "brightly.\n", TP);
		write("You set the firework on the ground and light the fuse. It begins "
			+ "to fizzle and then burns brightly.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 1:
		tell_room(environment(TO), "The "
			+ query_short() + " shoots into the sky.\n");
			TO->add_prop(OBJ_I_INVIS, 101);
		x++;
		set_alarm(3.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "BOOM!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "You wait for more, but there's nothing. "
			+ "It seems the " + query_short() + " was a dud.\n");
		TO->remove_object();
		return 1;
		break;
		
		
	}
 }
	