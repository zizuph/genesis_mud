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
	 string adj1 = "short";
	 string adj2 = "squat";
	 string name = "firecracker";
	 
	 set_name(name);
	 add_name("firework");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " is both short and squat. "
		+ "It's a bit of a dirty white in colour and about the size "
		+ "of a fat pea-pod. A small fuse extends from the bottom of "
		+ "the firecracker. You could light the " + name + ".\n");
	add_item("fuse", "There is a small piece of rolled paper sticking out of "
		+ "the bottom of the " + name + ". It looks like the type of thing "
		+ "you'd light.\n");
	add_item("fuse", "Light it. See what happens.\n");
	add_cmd_item( ({"fuse", name, "firecracker"}), "light", "@@do_light@@");
	
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
		tell_room(environment(TO), "The " + query_short() + " shakes and "
			+ "rattles on the ground.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "It begins to spin!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "Red and orange flames shoot out of the ends "
			+ "of the firecracker.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 4:
		tell_room(environment(TO), "A spark lands on you. Ouch!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 5:
		tell_room(environment(TO), "The " + query_short() + " starts jumping "
			+ "about, still spinning. The red and orange flames get even longer "
			+ "and more intense!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "ZZZZZZzzzzzzzzzzzzZZZZZZZZZzzzzzzzzzZZZZZ"
			+ ": The firecracker starts emitting a buzzing noise.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "The red and orange flames die down, but the "
			+ "noise gets louder. ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZzzz"
			+ "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 8:
		tell_room(environment(TO), "The firecracker abruptly stops and all is "
			+ "silent.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 9:
		tell_room(environment(TO), "The " + query_short() + " collapses into a pile of "
			+ "ash, its energies spent, and the wind blows it away.\n");
		TO->remove_object();
		return 1;
		break;
	
		
	}
 }
	