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
	 string adj1 = "black";
	 string adj2 = "box-shaped";
	 string name = "firework";
	 
	 set_name(name);
	 add_name("firecracker");
	 add_name("firework");
	 add_name("box");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " is just a box. It's six-sided, "
		+ "as boxes are, and black as onyx. From one corner, you see a "
		+ "short fuse. Otherwise, each side is exactly the same as the "
		+ "others. You could light the " + name + ".\n");
	add_item("side", "It's black and flat.\n");
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
			+ "to fizzle and then starts smoking.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 1:
		tell_room(environment(TO), "Smoke rings shoot out of the " + query_short() 
			+ " toward the sky.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 2:
		tell_room(environment(TO), "The smoke rings rock back and forth. Suddenly, a "
			+ "ship appears in their midst.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "More smoke rings belch forth from the " 
			+ query_short() + ". Another ship appears along with the new smoke "
			+ "rings.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 4:
		tell_room(environment(TO), "Suddenly, one of the ships turns broadside "
			+ "to the other. Smoke cannons fire red flames toward the second ship.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 5:
		tell_room(environment(TO), "The second ship bursts into flames and then "
			+ "shoots red, green, blue, and yellow fireworks into the sky.\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "The first ship dissolves slowly, bathed in "
			+ "the multi-colored glow of the fireworks display.\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "The " + query_short() + " sputters and "
			+ "smokes.\n");
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
	