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
#include <filter_funs.h>


string name;
int x = 0;
 void
 create_object()
 {
	 string adj1 = "brown";
	 string adj2 = "paper-bear";
	 name = "firework";
	 
	 set_name(name);
	 add_name("firework");
	 add_name("firecracker");
	 set_adj(adj1);
	 add_adj(adj1);
	 
	 set_short(adj1 + " " + adj2 + " " + name);
	 
	set_long("This " + query_short() + " looks like a brown grizzly bear. It "
		+ "fits comfortably in your hand. Its mouth is wide open and it looks"
		+ "fierce. A small fuse extends from the bottom of "
		+ "the firework. You could light the " + name + ".\n");
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
	 //Here we randomly select which living object to interact with
	int i = 0;
	object *ob;
	object target;
	ob = FILTER_LIVE(all_inventory(environment(TO)));
		for (i=0; i<sizeof(ob); i++)
		{
			target = ob[(random(i))];
		}
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
		tell_room(environment(TO), "The " + query_short() + " bursts into "
			+ "flames and disappears, leaving nothing behind but a brown "
			+ "sphere.\n");
		TO->add_prop(OBJ_I_INVIS, 101);
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 3:
		tell_room(environment(TO), "The sphere morphs into a giant grizzly bear!\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 4:
		
			tell_room(environment(TO), "The bear turns and chases " + 
				QCTNAME(target) + "!\n", target);
			target->catch_vbfc("The bear turns and starts chasing you!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 5:
		tell_room(environment(TO), "The grizzly bear knocks " + QCTNAME(target)
			+ " to the ground!\n", target);
		target->catch_vbfc("The grizzly bear knocks you to the ground!\n");
		x++;
		set_alarm(10.0, 0.0, do_light);
		return 1;
		break;
		
		case 6:
		tell_room(environment(TO), "The bear licks " + QTPNAME(target)
			+ " in the face and " + HE_SHE(target) + " starts laughing!\n",
			target);
		target->catch_vbfc("The bear licks you in your face, making you "
			+ "laugh!\n");
		x++;
		set_alarm(5.0, 0.0, do_light);
		return 1;
		break;
		
		case 7:
		tell_room(environment(TO), "The bear dissolves into a shower of "
			+ "brown lights.\n");
		
		TO->remove_object();
		return 1;
		break;
		
		
	}
 }
	