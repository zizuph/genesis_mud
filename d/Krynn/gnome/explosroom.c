/* The central-new-equipment-test-area of the Gnomes, by Dajala.
	A player who is in the room during an explosion, triggered
	from ~/corridor1.c will become paralyzed for some time.
*/

inherit "/d/Krynn/std/room.c";

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/sys/filter_funs.h"      /* to use FILTER_LIFE */

object gnome1, gnome2, para, wg, rock;

void
create_room()
{
	INSIDE;
	DARK;
	set_short("The Gnomes' Test area");
	set_long(
	  "This cave looks DANGEROUS! It's all smoke and noise in here "
	+ "so you can just barely make out what's happening. Or perhaps "
	+ "it's not the room that worries you, but these activities which "
	+ "take place in here. A large part of the northeastern wall "
	+ "has been blasted away by an explosion, "
	+ "the walls are blackened with smoke and there is a huge "
	+ "crater in the middle of the cave. In the center of the crater "
	+ "stands an odd apparatus.\nThere are iron tracks on the "
	+ "ground.\n");
	add_item(({"apparatus", "machine", "odd apparatus"}),
		"It is huge. There are several strange "
		+ "protrusions on the one side and some sort of chimney "
		+ "on the other. Strange noises and a lot of steam are "
		+ "coming from the inside. You get the strong impression "
		+ "that this device is going to blow up quite soon!\n");
	add_item("protrusions", "You haven't got the slightest idea what "
		+ "they might be good for. Some look like levers though.\n");
	add_item("crater", "It's about two feet deep and pitch "
		+ "black. It's filled with smoke but the strange "
		+ "apparatus cuts through the smoke clouds like "
		+ "a mountain.\n");
	add_item(({"tracks", "iron tracks"}), "They lead to the north.\n");
	add_item("dust", "You are COVERED with it!\n");
	add_item("smoke", "It's black, heavy and oily.\n");
	add_item(({"wall", "walls", "ground", "ceiling"}), "Blackened by "
			+ "smoke and surprisingly smooth.\n");

	add_cmd_item("lever", ({"push", "pull", "move"}), "@@move_lever");

	add_exit(TDIR + "corridor4.c", "northeast", "@@myexit", 10);
	add_exit(TDIR + "corridor5.c", "north", 0, 1);

	seteuid(getuid());
	set_alarm(1.0,-1.0, "reset_room");

	wg = clone_object (OBJ + "wagon.c");
	wg->move(TO);

	rock = clone_object("/d/Shire/common/obj/rock.c");
	rock->set_long("A piece of rock. It is completely useless.\n");
	rock->move(TO);
}


string
move_lever()
{
	if(query_internal_light() < 1)
		return "You cannot see!\n";
	write("You randomly choose a lever and move it.\n");
	write(
		"The machine shakes and rattles. A huge cloud of black, "
		+ "oily smoke is emerging from the chimney engulfing you. "
		+ "You cannot see for a second but hear a terrible "
		+ "screetching noise. When the smoke finally lifts again "
		+ "you can see the lever back in its original position.\n");
	tell_room(TO, 
		QTNAME(TP) + " does something dangerous to the machine and "
		+ "causes it to shake and rattle. " + PRONOUN(TP) + " is "
		+ "engulfed in a cloud of black, oily smoke.\n"
		+ "There is a terrible screeching noise.\n", TP);
	TP->command("cough");
	return "";
}

int 
myexit()
{
	write("You climb over the rubble and squeeze through the "
		+ "opening.\n");
	return 0;
}

string
inlight()
{
	if (query_internal_light() > 0)
		return "the ";
	else return "some ";
}

void 
paralyze_them()
{
	object *player;
	int i,ti;
	player = FILTER_LIVE(all_inventory(TO));
	seteuid(getuid(TO));
	for (i = 0; i < sizeof(player); i++)
	{	
		(player[i])->heal_hp(-((player[i])->query_max_hp(player[i]) / 8));
		if(((player[i])->query_hp()) < 0)
		{
			(player[i])->do_die();
			return;
		}
		para = clone_object("/std/paralyze");
		para->set_name("explpara");
		para->set_fail_message("You cannot do anything! "
			+ "You cannot see anything. "
			+ "You cannot feel anything. But that's OK because "
			+ "if you could, you might feel worse!\n");
		para->set_stop_message("You regain conciousness "
			+ "again. Each of your bones hurts!\n");
		ti = 61 + random(5);
		para->set_remove_time(ti);
		para->set_stop_verb("depart"); /* No command to stop the paralyze! */
		para->set_stop_object(0);      /* Use the messages set above */
		para->move(player[i], 1);
		player[i]->add_prop(LIVE_S_EXTRA_SHORT, " lies unconciously "
			+ "in a corner of the cave");   
	}
	set_alarm(30.0, -1.0, "expl5");
}

void 
release_them()
{
	object *player;
	int i;
	player = FILTER_LIVE(all_inventory(TO));
	for (i = 0; i < sizeof(player); i++)
	{
		para = present("explpara", player[i]);
		if (para)
		{
			player[i]->remove_prop(LIVE_S_EXTRA_SHORT);
		}
	}
	set_alarm(30.0, -1.0, "run_wagon1");
}

/* run_wagon starts the mining wagon after an explosion */

void
run_wagon1()
{
	if (present("wagon", TO))
	{
		if (gnome1)
		{
			gnome1->do_light();
			set_alarm(5.0, -1.0, "run_wagon2");
		}
		else if (gnome2)
		{
			gnome2->do_light();
			set_alarm(5.0, -1.0, "run_wagon2");
		}
	}
}

void
run_wagon2()
{
	wg->w_run_init();
}


/* Different stages towards the final explosion */

void
expl0()
{
	tell_room(TO, "You hear a low humming coming from "
		+ inlight() + "machine.\n");
	set_alarm(20.0, -1.0, "expl1");
}

void 
expl1()
{
	tell_room(TO, "The humming coming from " + inlight() + "machine "
			+ "grows louder.\n");
	set_alarm(20.0, -1.0, "expl2");
}

void 
expl2()
{
	tell_room(TO, capitalize(inlight()) + "machine starts to "
		+ "vibrate and rumble. Something is going to happen "
		+ "real soon!\n");
	set_alarm(20.0, -1.0, "expl3");
}

void 
expl3()
{
	tell_room(TO, "The very ground you are standing on starts to "
		+ "shake fiercely and little stones are falling from the "
		+ "ceiling.\n");
	if (query_internal_light() > 0)
		tell_room(TO, "A huge cloud of smoke is emerging from the "
		+ "apparatus' chimney.\n");
	set_alarm(20.0, -1.0, "expl4");
}

void 
expl4()
{
	tell_room(TO, "Suddenly there is a terrible explosion and the "
		+ "only thing you can see is light , fire and smoke. You "
		+ "feel yourself lifted from your feet and bashed against "
		+ "a wall. OUCH! Then there is complete darkness...\n");

	add_prop(ROOM_I_LIGHT, -10);
	paralyze_them();
	if(!P(rock, TO))
	{
		rock = clone_object("/d/Shire/common/obj/rock.c");
		rock->set_long("A piece of rock. It is completely useless.\n");
		rock->move(TO);
	}
}

void 
expl5()
{
	object *player;
	int i;
	player = FILTER_LIVE(all_inventory(TO));
	for (i = 0; i < sizeof(player); i++)
	{
		if (!present("explpara", player[i]))
		{
			player[i]->catch_msg("The smoke and dust settles down again.\n");
			if (query_internal_light() > 0)
				player[i]->catch_msg("Strangely enough the machine seems "
					+ "to be unaffected.\n");
		}
	}	
	add_prop(ROOM_I_LIGHT, 0);
	set_alarm(30.0, -1.0, "release_them");
}

void 
reset_room()
{
	if (!gnome1)
	{
		gnome1 = clone_object(MON + "exgnome");
		gnome1->move_living("xxx", TO);
	}
	if (!gnome2)
	{
		gnome2 = clone_object(MON + "exgnome");
		gnome2->move_living("xxx", TO);
	}
}


string
area() {return "Inthetestarea";}

string
wayout() {return "north northeast";}

string
tohelp() {return "north";}

string
fromhelp() {return "done";}
