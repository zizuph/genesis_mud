/*
** Unholy shrine in Cult of Melkor temple
**
** Gunther 940718
*/

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"
#include <ss_types.h>

init()
{
	::init();
	add_action("join_someone", "brand");
	add_action("declare_faith", "declare");
	add_action("break_bond", "break");
	add_action("read_runes", "read");
	add_action("ask_for_brazier", "brazier");
}

create_room()
{
	set_short("Unholy shrine.");
	set_long("An overwhelming feeling of evil comes over you"
		+" as you stand in this shrine of unholyness. The room"
		+" is lit by numerous black candles carefully placed"
		+" out in strange patterns, casting eerie reflections off"
		+" the various gargoyles and icons carved into the walls."
		+" In the back of the room stands an altar made from"
		+" black rock. A large coal brazier is burning in one"
		+" corner off the shrine.\nThere is a pink sign here that"
		+" looks VERY out of place.\n");
		
	add_item("sign", "The sign reads:\nHello and welcome to the"
		+" Cult of Melkor, oh willing servant of darkness. The guild"
		+" is currently not open, but you may leave a note on"
		+" the board in the entrance hall that you wish to be"
		+" sponsored into the guild when it does open.\n/Gunther"
		+" Immortal Disciple of Melkor\n");
		
	add_item(({ "icon", "icons", "gargoyle", "gargoyles" }),
		"You stare in awe at the detailed sculptures on the walls"
		+" and wonder if such creatures do in truth exist.\n");
	add_item(({ "walls", "wall" }), "The walls are carved from"
		+" the bedrock itself.\n");
	add_item(({ "candle", "candles" }),
		"The black candles seem only a little burned but you get"
		+" the feeling that they have lighted this place for a"
		+" very long time. Reaching closer to them you notice that"
		+" they aren't giving off any heat. In fact, they do not"
		+" seem to be burning at all!\n");
	add_item("altar", "The black altar is covered with runes done"
		+" in with a color so intensely black that it is hard to"
		+" distinguish them from holes in the stone. You have never"
		+" seen such runes elsewhere, but you feel that you could"
		+" still read them should you try to do so.\n");
	add_item("brazier", "The large brazier is filled with glowing"
		+" coals. A few branding irons hang on the side of it.\n");
	add_item("runes", "You think that you can read them.\n");
	add_item(({"irons", "branding iron", "iron", "branding irons" }),
		"The branding irons bear the mark of Melkor.\n");
	
	add_exit(CULT_DIR + "t_entr", "southeast", 0);
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
}

read_runes(string str)
{
	NF("Read what?\n");
	if(str != "runes") return 0;
	
	write("You read the runes:");
	/* insert history, rules and stuff here */
	say(QCTNAME(TP) + " studies the runes on the altar.\n");
	return 1;
}

leave_env(object ob, object to)
{
	if(ob->query_prop(I_HAVE_FAITH_IN_MELKOR))
		ob->remove_prop(I_HAVE_FAITH_IN_MELKOR);
	::leave_env(ob, to);
}

declare_faith(string str)
{
	NF("Declare what?");
	if(str != "faith") return 0;
	/* by doing this a player allows himself to be branded. */
	NF("You have already declared your faith in Melkor.\n");
	if(TP->query_prop(I_HAVE_FAITH_IN_MELKOR)) return 0;
	
	NF("Melkor will not accept those too much inclined towards good.\n");
	if(TP->query_align() > -300) return 0;
	
	write("You kneel down in front of the altar and declare"
		+" your faith in Melkor.\n");
	say(QCTNAME(TP) + " kneels down in front of the altar and"
		+" declares " + HIS(TP) + " faith in Melkor.\n");
	TP->add_prop(I_HAVE_FAITH_IN_MELKOR);
	return 1;
}

break_bond(string str)
{
	NF("Break what?");
	if(str != "bond") return 0;
	
	NF("You are not one of the Cult!\n");
	if(!TP->query_guild_member(CULT_NAME)) return 0;
	
	/* leave the guild */
	if(TP->remove_guild_occ());
	{
		write("As you withdraw your pledge to serve Melkor"
			+", you feel Him brutally ripping off contact, sapping your life force"
			+" as He goes. Death descends"
			+" upon you as your honor shatters into dust.\n");
		say(QCTNAME(TP)+ " has broken"
			+" the unholy pledge to Melkor.  You"
			+" watch quietly as death descends to take " + HIM(TP)
			+" away.\n");
		TP->set_hp(0);
		TP->do_die("Withdrawal from Cult of Melkor");
		
			/* Removal of skills */
		TP->set_skill(SS_SPELLCRAFT, 0);
		TP->set_skill(SS_FORM_ILLUSION, 0);
		TP->set_skill(SS_FORM_DIVINATION, 0);
		TP->set_skill(SS_FORM_ABJURATION, 0);
		TP->set_skill(SS_ELEMENT_DEATH, 0);
		TP->set_skill(SS_ELEMENT_EARTH, 0);
		TP->set_skill(SS_ELEMENT_WATER, 0);

		if (TP->query_default_start_location() == (CULT_DIR+"t_start"))
		{
			if (TP->query_race_name()=="elf")
				TP->set_default_start_location("/d/Genesis/start/elf/room/begin");
			if (TP->query_race_name()=="dwarf")
				TP->set_default_start_location("/d/Genesis/start/dwarf/lvl1/temple");
			if (TP->query_race_name()=="hobbit")
				TP->set_default_start_location("/d/Genesis/start/hobbit/v/church");
			if (TP->query_race_name()=="goblin")
				TP->set_default_start_location("/d/Genesis/start/goblin/caverns/quarters");
			if ((TP->query_race_name()=="human")||(TP->query_race_name()=="gnome"))
				TP->set_default_start_location("/d/Genesis/start/human/town/church");
		}
	}
	else
		write("There was some error.  You were unable to withdraw"
			+"\n from the Cult of Melkor.  Please leave a note on"
			+"\n the bulletin board here in the guild, and"
			+"\n we will attempt to solve the problem.\n");
			
	return 1;
	
}

join_someone(string str)
{  
	object *stuff, brandee;
	NF("Brand whom?\n");
	stuff = parse_this(str, "%l");
	if(!sizeof(stuff)) return 0;
	
	NF("Only members of the Cult are allowed to brand someone.\n");
	if(!is_member(TP)) return 0;
	
	brandee = stuff[0];
	NF("That person is already a member of an occupational guild!\n");
	if(brandee->query_guild_member(CULT_TYPE)) return 0;

	NF("That person has not declared faith in Melkor.\n");
	if(!brandee->query_prop(I_HAVE_FAITH_IN_MELKOR)) return 0;
	
	write("You take a branding iron from one of the pegs on the side of"
		+" the large brazier and put it on top of the glowing coals. A draft"
		+" flows through the holes drilled in the bottom of the brazier,"
		+" making the coals very hot.\n");	
	say(QCTNAME(TP) + " takes a branding iron from one of the pegs on the side of"
		+" the large brazier and puts it on top of the glowing coals. A draft"
		+" flows through the holes drilled in the bottom of the brazier,"
		+" making the coals very hot.\n");
	set_alarm(3.0, 0.0, brand02, TP, brandee);
	return 1;
}

void
brand02(object me, object brandee)
{
	set_this_player(me);
	
	tell_room(TO, "The iron is getting red.\n");
	set_alarm(3.0, 0.0, brand03, TP, brandee);	
}

void
brand03(object me, object brandee)
{
	set_this_player(me);
	
	tell_room(TO, "The iron is turning white around the edges.\n");
	set_alarm(3.0, 0.0, brand04, TP, brandee);	
}

int is_member(object me)
{
	if(me->query_guild_member(CULT_NAME)) return 1;
	else return 0;
}

void
brand04(object me, object brandee)
{
	object shadow, *list, braz;
	int result, n;

	set_this_player(me);
	
	tell_room(TO, "The iron is now white from the heat and ready to use, ");
	if(ENV(brandee) != TO)
	{
		tell_room(TO, "but " + QTNAME(brandee) + " is gone!\n");
		return;
	}
	if(ENV(TP) != TO)
	{
		tell_room(TO, "but " + QTNAME(TP) + " isn't here!\n");
		return;
	}
	
	TP->catch_msg("so you remove it from the fire. You grab hold of the back"
		+" of " + QTNAME(brandee) + "'s neck and twist " + HIS(brandee)
		+" head back slighty. Slowly you set the glowing iron to the"
		+" skin of " + HIS(brandee) + " cheek. There is a bubbling sound and"
		+" the smell of burnt flesh fills the room. You remove the iron"
		+" and place it on the peg, the work finished.\n");
	
	tell_room(TO, "so " + QTNAME(TP) + " removes it from the fire. " + HE(TP)
		+" grabs hold of the back of " + QTNAME(brandee) + "'s neck and twist "
		+ HIS(brandee)	+ " head back slighty. Slowly " + QTNAME(TP) + " sets the"
		+" glowing iron to the skin of " + QTNAME(brandee) + "'s cheek. There is a bubbling sound and"
		+" the smell of burnt flesh fills the room. " + QTNAME(TP) + " removes the iron"
		+" and places it on the peg, the work finished.\n", ({ TP, brandee }));
	
	brandee->catch_msg("so " + QTNAME(TP) + " removes it from the fire. " + HE(TP)
		+" grabs hold of the back of your neck and twist your head back slighty. Slowly "
		+ QTNAME(TP) + " sets the glowing iron to the skin of your cheek. There is a bubbling"
		+" sound and the smell of burnt flesh fills the room. You grunt a little from the"
		+" intense pain. " + QTNAME(TP) + " removes the iron"
		+" and places it on the peg, the work finished.\n");
	brandee->add_prop(LIVE_S_SOULEXTRA, "grimacing in pain");
	brandee->command("scream");
	
	/* ok add souls and shadows */
   NF("For strange reasons, the brand did not take hold. The aspiring player"
   	+" is not a member. Please contact the wizard guildmaster.\n");
	shadow = clone_object(CULT_DIR + CULT_SHADOW);

	result = shadow->shadow_me(brandee, CULT_TYPE, CULT_STYLE, CULT_NAME);
	if(result !=1 )
		NF("There is some error. Perhaps"
			+" the other guilds will not allow the aspiring player to"
			+" join our dark ways.\n");
		"/secure/master"->do_debug("destroy",shadow);
		return 0;
	}
	
	brandee->catch_msg("The voice of Melkor, or maybe someone else, flows"
		+" into your mind like an overwhelming torrent. It grips your brain"
		+" sending spasms of pain out into your body. The voice utters 'Serve"
		+" me well, slave!' and leaves as quickly as it came. You are now one"
		+" of the Cult of Melkor.\n");
	
	tell_room(TO, QCTNAME(brandee) + " suffers a few spasms of pain and briefly gets"
		+" a horrified look on " + HIS(brandee) + " face.\n", brandee);	
		
	TP->catch_msg("You have branded " + QTNAME(brandee) + " as one of the Cult of Melkor.\n");
	
	/* tell all cult members online that we got a new member */
	list = filter_array(users(),"is_member", TO);
	for(n = 0; n < sizeof(list); n++)
		if(list[n] != TP && list[n] != brandee)
			list[n]->catch_msg(QCTNAME(TP) + " has branded " + QTNAME(brandee) +
				" as one of the Cult. Use him well!\n");
	
	/* clone brazier */
	seteuid(getuid(TO));
	braz = clone_object(CULT_DIR + "brazier");
	if(!braz)
	{
		brandee->catch_msg("For some reason you were unable to get a brazier"
			+" though. Please tell someone about it.\n");
		return 0;
	}
	braz->move(brandee);
}

ask_for_brazier()
{  
	object braz;
	seteuid(getuid(TO));
	braz = clone_object(CULT_DIR + "brazier");
	NF("Couldn't get a brazier! Please make a bug report.\n");
	if(!braz) return 0;
	braz->move(TP);
}	






