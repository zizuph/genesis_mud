/*
** Cult of Melkor command object
**
** By Gunther 940719
*/


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

#define NO_COMMAND			0
#define GO_THERE				1
#define DONT_GO_THERE		2
#define KILL_THAT_GUY		3
#define DONT_KILL_THAT_GUY 4
#define REVENGE				5
#define LEAVE_HIM				6

/* global object variables */
int comstat;		/* the current command */
object anobject;	/* object, used differently depending on ongoing command */
string astring;	/* string, used differently depending on ongoing command */
time cominit;		/* time when command was given */

init()
{
	object en;
	::init();
	
	en = ENV(TO);
	if(en->query_prop(PLAYER_I_IS)) /* rightful owner then */
		en->add_subloc(CULT_SUBLOC, TO);
}	

string
show_subloc(string subloc, object on, object for_obj)
{
	if(subloc != CULT_SUBLOC) return "";
	if(on == for_obj)
		return "You are branded with the mark of Melkor.\n";
	if(for_obj->query_prop(PLAYER_I_IS) && for_obj->query_guild_member(CULT_NAME))
		return (HE(on) + " is branded with the mark of Melkor.\n");
	return (HE(on) + " has a brand on " + HIS(on) + " cheek.\n");
}		

create_object()
{
	set_name("_cult_command_obj");
	set_no_show();
	
	add_prop(OBJ_I_NO_SELL, 1);
	add_prop(OBJ_I_NO_DROP, 1);
	add_prop(OBJ_I_NO_GET, 1);
	add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_S_WIZINFO, "This object handles the commands 'sent by' Melkor for"
		+" the Cult of Melkor. It includes an alarm that every now and then checks"
		+" if its time to issue another command or if the time is up for the player,"
		+" in which case action is taken. It also has a function that the soul"
		+" calls when a player says he's completed a command. If correct he will be"
		+" rewarded. This object is meant to be autoloading.\n");
		
	set_alarm(60.0, 60.0, shall_we_command);
}

shall_we_command()
{  
	int n;
	if(comstat != NO_COMMAND)
	{
		remove_alarm(shall_we_command);
		return;
	}
	if(ENV(TO)->query_prop(PLAYER_I_IS)) set_this_player(ENV(TO)); else return;
	/* if they are attending a sacrifice, then lets not */
	if(present("_cult_sacrifice_obj", ENV(ENV(TO)))) return;

	if(random(10) != 7) return;
	
	n = random(7) + 1;
	switch(n) {
		case GO_THERE				: go_there();
		case DONT_GO_THERE		: dont_go_there();
		case KILL_THAT_GUY		: kill_that_guy();
		case DONT_KILL_THAT_GUY : dont_kill_that_guy();
		case REVENGE				: break;
		case LEAVE_HIM				: leave_him();
	}
}

show_to(string comm)
{
	string a, b, c;
	int n;
	
	n = random(6);
	switch(n) {
		case 0 : a = "The presence of Melkor rips through your head and you fall to your knees,"
						+" stunned. The agony is almost unbearable as He speaks:\n";
					b = "The presence leaves as quickly as it came and you stand up again, awed.\n";
					c = QCTNAME(TP) + " suddenly falls on " + HIS(TP) + " knees in pain, but seems to recover quickly.\n";
					break;
		case 1 : a = "A feeling of dread permeates your entire body and half a second later Melkor"
						+" makes it real by flooding into your conciousness. His voice grates on your"
						+" nerves as He speaks:\n";
					b = "Melkor departs from your mind leaving you with a feeling that He took a part"
						+" of it with Him.\n";
					c = QCTNAME(TP) + " gets dizzy for a short moment.\n";
					break;
		case 2 : a = "Sudden nausea overcomes you as Melkor enters your body. You try to force the"
						+" feeling down, but fail. He speaks:\n";
					b = "Melkor leaves and you remain with a feeling of loss and a slight taste of"
						+" stomach acid in your mouth.\n";
					c = QCTNAME(TP) + " doubles over and pukes.\n";
					break;
		case 3 : a = "Every muscle in your body suddenly springs taut as your small body is entered by"
						+" the large presence of Melkor. He speaks:\n";
					b = "All your muscles simultaneously relax when Melkor leaves and you find yourself"
						+" tired beyond belief.\n";
					c = QCTNAME(TP) + " arches backwards spasmoidically but quickly regains " + HIS(TP) + " footing.\n";
					break;
		case 4 : a = "An image of Melkor appears before you and you quickly throw yourself down on the ground in worship."
						+" The image seizes your head in a searingly painful grasp and its horrible eyes lock onto yours"
						+" as it speaks:\n";
					b = "The image disappears in a sudden haze of darkness.\n";
					c = QCTNAME(TP) + " quickly throws " + HIM(TP) + "self down onto the ground before something unseen. "
						+ HE(TP) + " remains on the ground for only a few seconds, then rises to " + HIS(TP) + " feet again.\n";
					break;
		case 5 : a = "All of a sudden all inanimate objects in your surroundings seem to speak with the voice of"
						+" Melkor, saying:\n";
					b = "Then all is quiet again.\n";
					c = QCTNAME(TP) + " stops as if to listen to something.\n";
					break;
	}
	write(a + comm + b);
	say(c);
}

is_npc(object ob)
{
	if(ob->query_prop(PLAYER_I_IS)) return 0;
	return 1;
}

query_command_string() { return astring; }
query_command_target() { return anobject; }
/******************************************** command code ********************************************/

dont_kill_that_guy()
{
	object target;
	target = TP->query_attack();
	if(!target) return;
	
	/* ok, lets appear! */
	comstat = DONT_KILL_THAT_GUY; 
	astring = "Do not kill " + QTNAME(target) + "! I have other plans for that one, and I want it alive.\n";
	show_to(astring);
	anobject = target;
	set_alarm(600.0, 0.0, eot_dktg); /* 10 mins */
}

eot_dktg()
{
	object en;
	en = ENV(TO);
	if(!en->query_prop(PLAYER_I_IS)) return;
	set_this_player(en);
	
	/* check that anobject is alive still */
	if(!anobject || anobject->query_ghost())
	{
		/* FAIL */
		show_to("You failed me, and did not protect the one I wished to spare!\n");
		add_some_favor(-100);
	}
	else
	{
		show_to("Good, it is still alive. Well done, I have no more need of it now and you may do as you please with it.\n");
		add_some_favor(15);
	}
	comstat = NO_COMMAND;
	
	set_alarm(60.0, 60.0, shall_we_command);
}

kill_that_guy()
{
	/* check if TP is in a room with NPC's in it */
	object *others, *npc;
	int n;
	
	others = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
	npc = filter(others, "is_npc", TO);
	if(!sizeof(npc)) return;
	
	n = random(sizeof(npc));
	/* check that player is allowed to attack it */
	if(NATTACK(npc[n])) return;
	/* ok command */
	comstat = KILL_THAT_GUY;
	astring = "Make an example of " + QTNAME(npc[n]) + ". Kill it.\n";
	anobject = npc[n];
	set_alarm(1800.0, 0.0, eot_ktg);
}

eot_ktg()
{
	object en;
	en = ENV(TO);
	if(!en->query_prop(PLAYER_I_IS)) return;
	set_this_player(en);
	
	/* check that anobject is dead */
	if(anobject || !anobject->query_ghost())
	{
		show_to("You have failed me! " + QCTNAME(anobject) + " is still alive.\n");
		add_some_favor(-50);
	}
	else
	{
		show_to("Good. It is dead.\n");
		add_some_favor(50);
	}
	comstat = NO_COMMAND;
	
	set_alarm(60.0, 60.0, shall_we_command);
}

#define ROOMS ({ \
	"/d/Rhovanion/common/cult_guild/t_gather",		\
	"/d/Emerald/room/mountain/top"          			\
	})
	
#define NAMES ({ \
	"the cult temple gathering hall" \
	"the top of Mount Black in Emerald" \
	})

go_there()
{
	object *oc, gto;
	int n, m;
	/* a large array of places needed for this one */
	/* about 150 or so */
	oc = get_other_command_object(GO_THERE);
	n = random(1 + sizeof(oc));
	if(!n)
	{
		/* new place */
		m = random(sizeof(ROOMS));
		astring = "Go to " + NAMES[m] + ".\n";
		anobject = ROOMS[m];
	}
	else
	{
		astring = oc[n-1]->query_command_string();
		anobject = oc[n-1]->query_command_object();
	}
	show_to(astring);

	geteuid(setuid(TO));
	gto = clone_object("_go_there_obj");
	gto->set_player(TP);
	gto->move(anobject);
	comstat = GO_THERE;
	set_alarm(1800.0, 0.0, eot_gt);
}

eot_gt()
{
	object en;
	en = ENV(TO);
	if(!en->query_prop(PLAYER_I_IS)) return;
	set_this_player(en);

	show_to("You have not travelled where I directed you.\n");
	add_some_favor(-40);
	comstat = NO_COMMAND;
}

dont_go_there()
{
	object *oc, dgto;
	int n, m;	
	/* a large array of places needed for this one */
	/* about 150 or so */
	oc = get_other_command_object(GO_THERE);
	n = random(1 + sizeof(oc));
	if(!n)
	{
		/* new place */
		m = random(sizeof(ROOMS));
		astring = "Stay away from " + NAMES[m] + ".\n";
		anobject = ROOMS[m];
	}
	else
	{
		astring = oc[n-1]->query_command_string();
		anobject = oc[n-1]->query_command_object();
	}
	show_to(astring);

	geteuid(setuid(TO));
	gto = clone_object("_dont_go_there_obj");
	gto->set_player(TP);
	gto->move(anobject);
	comstat = DONT_GO_THERE;
	set_alarm(1800.0, 0.0, eot_dgt);
}

eot_dgt()
{
	object en;
	en = ENV(TO);
	if(!en->query_prop(PLAYER_I_IS)) return;
	set_this_player(en);

	show_to("You have gone where you were not allowed to.\n");
	add_some_favor(-100);
	comstat = NO_COMMAND;
}

revenge(object fellow, object target)
{
	/* this command is started by do_die in the shadow */
	astring = fellow->query_name() + " was killed by " + QTNAME(target) + ". Avenge " + HIM(fellow) + "!\n";
	anobject = target;
	comstat = REVENGE;
	set_alarm(1800.0, 0.0, eot_revenge);
}
	
eot_revenge()
{
	show_to("So, we will bide our time and avenge my slave at another time.\n");
	comstat = NO_COMMAND;
}

	
