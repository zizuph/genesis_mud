inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#include "/sys/ss_types.h"

#define BS(message)     break_string(message,75)
#define PS(message)	process_string(message)
#define TP              this_player
#define TO              this_object
#define MYS_SKILL	130001

object			the_room;
int			amount_burned = 0;
int			lit_flag = 0;

void
init()
{
    ::init();
    add_action("do_light", "light");
    add_action("do_unlight", "extinguish", 1);
}

do_sleep(object player, object *r_list)
{
    object  para_ob;
    int	    i;
    
    tell_object(player, "The fumes of the candle overcome you, and you fall into an unconscious slumber.\n");
    for (i=0; i<sizeof(r_list); i++)
	    if (living(r_list[i])&&r_list[i]!=player&&!present("candle_para", player))
		tell_object(r_list[i], PS(QCTNAME(player)+" collapses, overcome by the fumes!\n"));
    para_ob=clone_object("/std/paralyze.c");
    para_ob->set_standard_paralyze("foobar");
    para_ob->set_name("candle_para");
    para_ob->set_stop_verb("drivew");
    para_ob->set_fail_message(BS("You exert your will to the utmost, but it does "
    + "no good..you are unconcious for the duration.\n"));
    para_ob->set_stop_message("You awaken from the unnatural sleep, with a headache "
    + "worthy of the Gods.\n");
    para_ob->set_remove_time(45);
    para_ob->move(player);
}

void
do_affect(object player, object *rm_list)
{
    int	    i;
    
    if (present("candle_para", player))
	return;
    tell_object(player, BS("The evil, overbearing fumes of the candle fill "
		+ "your senses and cloud your mind. Your eyes grow heavy and your muscles "
		+ "tremble underneath you.\n"));
    if (random(50)>player->query_stat(SS_CON))
    {
	do_sleep(player, rm_list);
	return;
    }
    else
    {
	tell_object(player,"With difficulty, you shake off the effects of the corrupt fumes.\n");
	for (i=0; i<sizeof(rm_list); i++)
	    if (living(rm_list[i])&&rm_list[i]!=player&&present("candle_para", player)!=0)
		tell_object(rm_list[i], PS(BS(QCTNAME(player)+" seems to stumble, but takes a step and recovers. Funny, "
		+ player->query_pronoun()+ " doesn't look that drunk..\n")));
	player->set_fatigue(player->query_fatigue()-10);
    }
}

void
do_wake(object player)
{
    object  para_ob;
    
    if (para_ob = present("candle_para", player))
	para_ob->stop_paralyze();
}

string
how_much()
{
    switch(amount_burned)
    {
	case 0: return "The candle has never been lit.";
	case 1: return "The candle is almost whole.";
	case 2: return "The candle has burned perhaps a fourth of the way down.";
	case 3: return "The candle is about half gone.";
	case 4: return "Most of the candle has burned away.";
	case 5: return "The candle is almost gone; only a stub remains.";
    }
}

string
is_lit()
{
    if (lit_flag) 
	return "The candle is burning; a vile, putrid odor fills this place.";
    else 
	return "The candle is not lit.";
}

string
short_is_lit()
{
    if (lit_flag)
	return " (burning)";
    else
	return "";
}

void
create_object()
{
    set_name("candle");
    add_name("mys_sleep_bomb");
    add_adj(({"short", "black"}));
    set_short("black candle@@short_is_lit@@");
    set_long(BS("This short squat candle is so black you almost doubt its existence. "
    + "A strip of metallic foil, bearing a strange seal resembling an intricate "
    + "silver star, is wrapped around the bottom of the taper. The wax reeks of "
    + "vile rot and corrupt death, and other evil fumes whose exact nature "
    + "eludes you.\n")
    + "@@how_much@@\n@@is_lit@@\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
}

void
burn_0()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		do_affect(room_list[i], room_list);		
	    }
	call_out("burn_1", 30);
    }
}

void
burn_1()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
		do_affect(room_list[i], room_list);		
	call_out("burn_2", 30);
    }
}

void
burn_2()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		do_affect(room_list[i], room_list);		
	    }
	call_out("burn_3", 30);
    }
}

void
burn_3()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		do_affect(room_list[i], room_list);		
	    }
	call_out("burn_4", 30);
    }
}

void
burn_4()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		do_affect(room_list[i], room_list);		
	    }
	call_out("burn_5", 30);
    }
}

void
burn_5()
{
    int	    i;
    object  *room_list;
    
    if (lit_flag)
    {
	amount_burned++;
	room_list = all_inventory(environment(TO()));
	for (i=0;i<sizeof(room_list);i++)
	    if (living(room_list[i]))
	    {
		do_affect(room_list[i], room_list);
		call_out("do_wake", 10, room_list[i]);	
	    }
	tell_room(environment(TO()), "The candle gutters and dies.\n"
	+ "The vile stench soon disperses.\n");
	remove_object();
    }
}

int
do_light(string str)
{
    object  ob;

    notify_fail("Light what?\n");    
    if (!parse_command(str+" ", environment(TP()), "%o", ob))
	return 0;
    if (ob!=TO())
	return 0;
    if (lit_flag)
    {
	notify_fail("But the candle is already lit!\n");
	return 0;
    }
    if (living(environment(TO())))
    {
	notify_fail(BS("You sense somehow that to light the black candle "
	+ "in your own hands would be a Bad Idea.\n"));
	return 0;
    }
    lit_flag = 1;
    write(BS("You light the dark candle, and the air soon fills with a "
    + "putrid stench. Inhaling the vile odor, your eyes cloud and your mind "
    + "begins to blur. You feel sluggish as your vitality is drained, and "
    + "you feel, as if from a great distance, consciousness begin to slip away..."
    + "You realize, too late, the evil import of what you have done.\n"));
    TP()->set_alignment(TP()->query_alignment()-100);
    say(BS(QCTNAME(TP())+" lights the dark candle, and the air soon fills with a "
    + "putrid stench. Inhaling the vile odor, your eyes cloud and your mind "
    + "begins to blur. You feel sluggish as your vitality is drained, and "
    + "you feel, as if from a great distance, consciousness begin to slip away...\n"));
    amount_burned++;
    add_prop(OBJ_M_NO_GET, "The cursed flame is not to be moved while burning.\n");
    call_out("burn_"+amount_burned, 30);
    return 1;
}

int
do_unlight(string str)
{
    object  ob;

    notify_fail("Extinguish what?\n");    
    if (!parse_command(str+" ", environment(TP()), "%o", ob))
	return 0;
    if (ob!=TO())
	return 0;
    if (!lit_flag)
    {
	notify_fail("But the candle is not lit!\n");
	return 0;
    }
    lit_flag = 0;
    write(BS("Thankfully, you extinguish the candle, and the vile stench soon "
    + "vanishes.\n"));
    say(BS(QCTNAME(TP())+" extinguishes the candle, and the vile stench soon "
    + "vanishes.\n"));
    add_prop(OBJ_I_NO_GET, 0);
    return 1;
}


