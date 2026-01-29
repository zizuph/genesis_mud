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
	 string adj1 = "long";
	 string adj2 = "tubular";
	 string name = "firework";
	 
	 set_name(name);
	 add_name("firecracker");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " is about as long as a goblin's "
		+ "arm, and thick around as two or three fingers. There is a base "
		+ "on the bottom with a fuse sticking out from it, and a hollow "
		+ "opening on the top. You could light the " + name + ".\n");
	add_item( ({"opening", "top"}), "On the top of the " + query_short()
		+ " is an opening about as wide as two or three fingers. When "
		+ "the " + name + " is on the ground, the opening will face "
		+ "the sky.\n");
	add_item( "base", "The base of the " + name + " is about as wide "
		+ "as your hand, with all your fingers splayed open. It provides "
		+ "a solid stand for the " + name + ".\n");
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
		tell_room(environment(TO), "The " + query_short() + " begins to shoot "
			+ "sparks toward the sky.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "The sparks merge into a fireball and shoot "
			+ "up, up, up!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "The fireball begins to elongate, looking like "
			+ "a worm...\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 4:
		tell_room(environment(TO), "No! It's a dragon!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 5:
		tell_room(environment(TO), "The dragon turns and looks toward you, "
			+ "it's mouth wide open, teeth made of fire.\nYou see a sparkle "
			+ "in its eye!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "The dragon swoops down and closes its mouth "
			+ "around you! You can feel the flames lick the hairs on the back "
			+ "of your neck.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "The dragon flies back up into the sky and "
			+ "explodes into a rainbow of sparks, which trickle back down to "
			+ "the ground.\nYou remember it wasn't a dragon at all, but just "
			+ "a " + query_short() + ".\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 8:
		tell_room(environment(TO), "The " + query_short() + " sputters and "
			+ "smokes.\n");
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
	