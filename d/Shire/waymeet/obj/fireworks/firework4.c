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

int x = 0;
 void
 create_object()
 {
	 string adj1 = "rainbow-tipped";
	 string adj2 = "arrow-shaped";
	 string name = "firecracker";
	 
	 set_name(name);
	 add_name("firework");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " looks like fat arrow. Instead of "
		+ "fletching, the arrow has a stand at its base. You can see a small "
		+ "fuse extending from the base. The tip looks like "
		+ "a fat rainbow arrow head. You could light the " + name + ".\n");
	add_item("fuse", "There is a small piece of rolled paper sticking out of "
		+ "the bottom of the " + name + ". It looks like the type of thing "
		+ "you'd light.\n");
	add_item( ({"tip", "fat tip", "rainbow tip", "fat rainbow tip"}),
		"The tip looks like an arrow head, but its over a finger wide. "
		+ "It has red, orange, yell, blue, and violet stripes on it, "
		+ "making it rainbow colored.\n");
	add_cmd_item( ({"fuse", name, "firecracker", "firework"}), "light", "@@do_light@@");
	
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
 
 mixed
 do_light()
 {
	 if(environment(TP)->query_prop(ROOM_I_INSIDE) && x == 0)
	 {
		 write("You'll need to light the " + query_short()
			+ " outside!\n");
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
		tell_room(environment(TO), "A red fireburst shoots "
			+ "from the " + query_short() + " to the sky.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "The red fireburst explodes, peppering the "
			+ "sky with red dots that seem to remind you of the sunrise. "
			+ " You look up, waiting for what's next.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "An orange fireburst shoots from the " 
			+ query_short() + ", followed almost immediately by a yellow one.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 4:
		tell_room(environment(TO), "The orange fireburst grows into a circle, "
			+ "and behind it the yellow expands until the two together look "
			+ "like the sun.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 5:
		tell_room(environment(TO), "The sun twinkles and disolves into what "
			+ "looks like thousands of sparks.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "A small green ball rises from the firework and "
			+ "then winks out so fast you almost missed it--the fabled green flash.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "A shower of violet flames erupt, but impossibly "
			+ "the flames seem to darken the sky, like night. And just like that, the "
			+ "firework is still.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 8:
		tell_room(environment(TO), "The " + query_short() + " collapses into a pile of "
			+ "ash, its energies spent, and the wind blows it away.\n");
		TO->remove_object();
		return 1;
		break;
	
		
	}
 }
	