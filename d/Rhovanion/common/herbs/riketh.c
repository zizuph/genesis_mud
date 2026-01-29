/*
 * This is a herb for the Smaug Esgaroth quest
 *
 * written by: Blackstaff
 *
 * with a lot of help from Elessars blind_ob.c
 *
 * Pressing this mushroom will make you blind for a while.
 *
 *
 * date: 950125
 */
inherit "/std/herb";

#include "/sys/stdproperties.h"
#include "macros.h"

int old_prop,time;

void 
create_herb()
{
	set_short("dry frail fungus");
	set_adj("dry");
	add_adj("frail");
	set_name("fungus");
	set_herb_name("riketh");
	set_id_long("This is a riketh mushroom. If you press it spores will " +
		"fly all over the place. ");
	set_unid_long("This is some kind of mushroom.\n");
	set_id_diff(25);
	set_find_diff(2);
}

void
init()
{
	::init();
	add_action("my_press","press");
	time=40;
}


void
do_blind()
{
	old_prop=this_player()->query_prop(LIVE_I_SEE_INVIS);
	this_player()->add_prop(LIVE_I_SEE_INVIS, -1);
	call_out("can_see_again", time);
	time=0;
}


int my_press(string str)
{
if (str=="mushroom" || str=="riketh" || str=="fungus")
	{
	say(QTNAME(this_player()) +" presses a mushroom and suddenly" +
			" a cloud of spores fly into his eyes.\n");
	write("You press the mushroom and spores fly into your eyes, blinding you." +
	" You feel a wave of nausea overwhelming you.\n");
	do_blind();
	return 1;
	}
else
	{
	write("press what ?");
	return 0;
	}
}
		



void
can_see_again()
{
	if(time <1)
	{	
		this_player()->add_prop(LIVE_I_SEE_INVIS, old_prop);
		write("Your tears seems to have cleared your eyes from the spores.\n");
	}
time=40;
}

void
set_time(int i)
{
	time +=i;
}
