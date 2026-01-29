inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>

#include "/d/Gondor/defs.h"

void
create_room() 
{
    set_short("Inside a well, just above the water level");
    set_long(BSN("You find yourself inside this little well. It is quite dark in "
	+ "here, there is only little light falling down the shaft of the well. "
	+ "There is a rusty ladder nailed to the wall. Below you there is water. "
	+ "You see a hatch in the west wall. You can climb up the ladder, and if "
	+ "you dare, you might try to dive into the water."));
    add_exit(EDORAS_DIR + "in_well2", "up", 0);
    add_item(({"ladder","rusty ladder"}), BSN("This ladder is strong enough to "
	+ "hold you. Or maybe it will break under your weight. The only way to "
	+ "know is to try it. It seems to continue down into the water, but if you "
	+ "want to climb down, you probably will have to dive."));
    add_item("water",BSN("The musty, dark water looks dirty and smells bad. "
	+ "But you think you can dive down into it."));
    add_item("hatch",BSN("This rusty hatch is closed and you don't think you can open it."));
    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    BEACH;
}

void
init() 
{
    add_action("do_enter","enter");
    add_action("broken","open");
    add_action("broken","close");
    add_action("do_dive","dive");
    add_action("do_dive","swim"); 
    add_action("do_breath","take");
    TP->add_prop("_breath",6);
    TP->add_prop("_breath_int",2);
    TP->add_prop("_breath_int_times",2);
    ::init();
}

int
do_enter(string str)
{
    if (str == "hatch")
    {
	NF("The little hatch is closed.\n");
	return 0;
	/*
		write("You enter the little hatch.\n");
		TP->move_living("into the hatch","EDORAS_DIR + "dungeon1");
		return 1;
	*/       
    }
    else
    {
	NF("Enter what?\n");
	return 0;
    }
}

int
broken(string str) 
{
    if (str == "hatch")
    {
	write("You can't do that. The hatch is broken.\n");
	say(QCTNAME(TP)+" fumbles with the hatch.\n");
	return 1;
    }
    return 0;
}

int
do_dive(string str)
{
    int swim_skill, i;
    object *inv_list;
    swim_skill = TP->query_skill(SS_SWIM);
    if(swim_skill >= 10) 
    {
	write("You dive into the musty water. \n");
	inv_list = deep_inventory(TP);
	for(i = 0; i < sizeof(inv_list); i++)
	{
	    if(inv_list[i]->query_prop("_obj_i_light"))
	    {
		if(function_exists("extinguish_me",inv_list[i]))
		{
		    write(BSN("When it touches the water, your " + inv_list[i]->query_name() +
			" goes out with a loud hiss."));
		    inv_list[i]->extinguish_me();
		    say("A " + inv_list[i]->query_name() + " goes out when " + QCTNAME(TP) +
		      " dives into the water.\n");
		}
		else if(function_exists("create_object",inv_list[i]) == "/std/torch")
		{
		    write(BSN("When it touches the water, your " + inv_list[i]->query_name() +
			" goes out with a loud hiss."));
		    inv_list[i]->add_prop("_obj_i_light",0);
		    say("A " + inv_list[i]->query_name() + " goes out when " + QCTNAME(TP) +
		      " dives into the water.\n");
		    TO->update_light();
		}
		else if(inv_list[i]->query_name() == "torch" || inv_list[i]->query_name() == "lamp")
		{
		    write(BSN("When it touches the water, your " + inv_list[i]->query_name() +
			" goes out with a loud hiss."));
		    inv_list[i]->add_prop("_obj_i_light",0);
		    say("A " + inv_list[i]->query_name() + " goes out when " + QCTNAME(TP) +
		      " dives into the water.\n");
		    TO->update_light();
		}
	    }
	}  
	TP->move_living("into the water",EDORAS_DIR + "in_well4",1);
	write(BS("You are under water now. If you run out of breath before you can "
	    + "come up for air again, you will drown. Hopefully, you took a breath "
	    + "before you came down here. Don't stay under water for too long.\n"));
	return 1;
    }
    else if(swim_skill > 0) 
    {
	write("You realize you should learn to swim better before you go down there.\n");
	return 1;
    }
    else  
    {
	write("You cannot swim! You would drown in the water!\n");
	return 1;
    }
}

int
do_breath(string str)
{
    int bt;
    if (str != "breath"  && str != "a breath") return 0;
    bt = (TP->query_stat(SS_CON)+TP->query_skill(SS_SWIM))/10;
    if(bt < 1) bt = 1;
    if(bt > 6) bt = 6;
    TP->add_prop("_breath", 5 + bt);
    write("You take a deep breath of air and prepare to dive...\n");
    say(QCTNAME(TP) + " takes a deep breath of air and prepares to dive...\n");
    return 1;
}

void
drop_item(object ob)
{
    string down_room;

    down_room = EDORAS_DIR + "in_well4";
    if (ob && present(ob))
    {
	tell_room(TO, "The " + ob->query_name() + " falls down.\n");
	if (ob->query_prop(OBJ_I_WEIGHT) < ob->query_prop(OBJ_I_VOLUME))
	{
	    tell_room(TO, "It splashes into the water, then remains floating "
	      + "there, too light to sink.\n");
	}
	else
	{
        tell_room(TO, "It hits the water with a splash, and sinks "
          + "into the murky depths.\n");
	    ob->move(down_room);
	    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
	    down_room->drop_item(ob);
	}
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!living(ob))
	set_alarm(1.0, 0.0, &drop_item(ob));
}
