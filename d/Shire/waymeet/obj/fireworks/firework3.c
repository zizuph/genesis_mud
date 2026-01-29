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
	 string adj1 = "yellow";
	 string adj2 = "flower-shaped";
	 string name = "firecracker";
	 
	 set_name(name);
	 add_name("firework");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " looks like a sunflower. It's round and "
		+ "somewhat flat. It looks like two concentric ciricles, the inner "
		+ "almost pitch black, and the outer a series of small yellow triangles "
		+ "that resemble petals. You can see a fuse extending from the outer "
		+ "circle. You could light the " + name + ".\n");
	add_item("fuse", "There is a small piece of rolled paper sticking out of "
		+ "the bottom of the " + name + ". It looks like the type of thing "
		+ "you'd light.\n");
	add_item("circle", "Did you mean the inner or outer circle?\n");
	add_item( ({"inner circle", "inner"}), "The inner circle is almost pitch "
		+ "black.\n");
	add_item( ({"outer", "outer circle"}), "The outer circle consists of "
		+ "yellow folded paper that looks like sunflower petals. A fuse "
		+ "extends from the outer circle.\n");
	add_item("fuse", "Light it. See what happens.\n");
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
		tell_room(environment(TO), "A short green vine, made of flames, extends "
			+ "from the " + query_short() + " to the sky.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "A yellow flower appears on top of the vine!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "The flower grows, larger and lager, reaching "
			+ "the size of an ogre's head and spitting sparks in every direction.\n");
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
		tell_room(environment(TO), "The flower shoots up to the sky, leaving behind the "
			+ "vine, which withers and dies. The flower, though, expands further "
			+ "until it seems almost as big as the sun!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "Small sunflowers begin to form from the "
			+ "sparks being shot off of the larger flower, until you feel "
			+ "like you're looking at a whole field of yellow sunflowers!\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "All at once, and together, the sunflowers "
			+ "explode, sending sparks through the sky like falling stars.\n");
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
	