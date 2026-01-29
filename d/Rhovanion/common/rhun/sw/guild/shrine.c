
inherit "/d/Rhovanion/lib/room";
inherit "/lib/guild_support";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw.h"

create_room()
{
	set_short("Unholy shrine");
	set_long("You have stepped down into a huge stone chamber"
		+" with a high vaulted ceiling and polished"
		+" stone walls.  The chamber is lit by many torches along the"
		+" walls.  It is still dim here, despite the"
		+" stones' reflections of the torchlight.  Everything here is"
		+" crafted of dark stone.  The eastern wall, at the head of this"
		+" unholy shrine, is covered with thousands of tiny runes,"
		+" though only a scarce few are recognizable.  A tangible evil,"
		+" cold and cunning, seems to lurk overhead, just inside the shadows"
		+" in the high corners of this"
		+" chamber.  It awaits new servants to call forth the"
		+" powers of darkness.  A board of some unidentifiable dark wood"
		+" hangs near to the entrance.  An age-old parchment, crinkled and"
		+" yellowed by time, is nailed to the board; you will want to"
		+" look closer at it for more instructions.  The only exit from"
		+" this shrine of darkness is the few steps that head back through"
		+" the low stone arch to the west.\n");
	
	add_exit(SWG+"arrive","west",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_item(({"wall","walls","stone","stones"}), "Everything"
		+" in this vaulted chamber is crafted from that same dark, polished"
		+" stone.  You wonder where, geographically, this"
		+" place is, and where such stone came from.\n");
	add_item("torches","The torches which light this chamber"
		+" are securely fastened to the walls.  They provide only the"
		+" scantest light, leaving the area still"
		+" dark and somehow discomforting.\n");
	add_item(({"ceiling","roof","arch","archways","archway","arches"})
		,"The ceiling here is supported by high stone arches,"
		+" crafted from that same material as the rest of the"
		+" room.  A smaller archway leads out to the west.\n");
	add_item("steps","A few stone steps lead up and"
		+" out of this unholy shrine to the west.\n");
	add_item(({"east","east wall","eastern wall","rune","runes"}),
		"The east wall, at the head of this unholy"
		+" shrine, is covered with many thousands of runes,"
		+" the working materials of the Spellweavers.  The meanings of most"
		+" of them, however, have been lost over time; now,"
		+" only a handful are recognized, and most of these only by the most"
		+" powerful, wizened, and experienced of the"
		+" Spellweavers.\n");
	add_item("shadows","You wonder at what evil"
		+" lurks in these shadows.\n");
	add_item(({"board","wood","parchment"}),
		"The aged parchment reads:  `Welcome, those of dark heart"
		+", to the unholy shrine of the Spellweavers.  Here, you may read the"
		+" history of the Spellweavers, or read the rules of joining our "
		+"ranks and serving the dark forces (<read history>,<read rules>)."
		+"  You may also pledge your servitude to the dark"
		+" powers we serve, either as occupational or layman (<pledge occ>,"
		+"<pledge lay>)-- but be warned!  Read all rules thoroughly first, as"
		+" the penalty for withdrawing your pledge is a severe one.  If you"
		+" must, you may <withdraw> from the ranks of the"
		+" Spellweavers, and accept the penalty of your actions.  Additionally, "
		+"it is possible to <alter> your guild membership here from layman to"
		+" occupational, or vice versa.  You may also"
		+" <list> the guilds to which you belong, or <kneel>"
		+" down to meditate, if you are a member of this dark guild."
		+"  Sponsors may invite their candidates into this room to join"
		+" the Spellweavers if they feel the candidate is worthy by using"
		+" <sponsor 'name'>.  Please invite only the truly"
		+" worthy and dark into our unholy shrine.'"
		+"\n");
}

init()
{
	::init();
	init_guild_support();
	add_action("join","pledge");
	add_action("my_leave","withdraw");
	add_action("list","list");
	add_action("literature","read");
	add_action("inviting","sponsor");
	add_action("alter_membership", "alter");
}

join(string str)
{
	object shadow;
	int result;

	notify_fail("The dark forces reject you!  You"
		+" cannot join the Spellweavers in your current state.\n");
	if(!do_I_want_this_player_in_my_guild(this_player()))
		return 0;

	notify_fail("You belong to a guild which the Spellweavers cannot accept.\n");
	if((!other_o(this_player()))&&((str=="occ")||(str=="occupational")))
		return 0;
	if((!other_l(this_player()))&&((str=="lay")||(str=="layman")))
		return 0;

	notify_fail("For strange reasons, you were unable to join.\n");

	if ((str=="occ")||(str=="occupational"))
		shadow = clone_object(SHADOW_O);
	if ((str=="lay")||(str=="layman"))
		shadow = clone_object(SHADOW_L);

	if ( ( ((result=shadow->shadow_me(this_player(),GTO,
			GUILD_STYLE,GUILD_NAME))!=1)
	&&((str=="occ")||(str=="occupational")) ) ||
	   ( ((result=shadow->shadow_me(this_player(),GTL,
		GUILD_STYLE,GUILD_NAME))!=1)
	    && ((str=="lay")||(str=="layman")) ) )
	{
		notify_fail("There is some error.  Perhaps"
			+" your other guilds will not allow you to"
			+" join our dark ways.\n");

		"/secure/master"->do_debug("destroy",shadow);
		return 0;
	}
	write("A strange dark cloud surrounds you momentarily."
	+"  You feel a rush of power of the dark forces behind the"
	+" runes fill your soul.  Congratulations, you are now a Spellweaver."
	+"\n");
	say(QCTNAME(this_player())+ " is momentarily"
		+" surrounded by a dark cloud, and you realize that a new"
	+" Spellweaver has joined the ranks of the servants of the"
		+" dark forces.\n");
}

do_I_want_this_player_in_my_guild(player)
{
	if (player->query_guild_member(GUILD_NAME))
	{
		notify_fail("You are already a"
			+" member of the Spellweavers.\n");
		return 0;
	}

	if (player->query_alignment()>-310)
	{
		notify_fail("Your soul tends too far towards"
			+" the light to be accepted here."
			+"  Embrace the darkness further; then return.\n");
		return 0;
	}
	return 1;
}

other_o(player)
{
		if(this_player()->query_guild_member(GTO))
	{
		notify_fail("You are already a member of another "+GTO
			+" guild.\n  ");
		return 0;
	}
	return 1;
}

other_l(player)
{
	if (this_player()->query_guild_member(GTL))
	{
		notify_fail("You are already a member of another "+GTL
			+" guild.\n");
		return 0;
	}
	return 1;
}

list()
{
	string str;

	str=this_player()->list_major_guilds();
	if(str)
		write("You are a member of the following guilds:\n"+str);
	else
		write("You are not a member of any guild.\n");
	return 1;
}

my_leave()
{
	notify_fail("You cannot withdraw from the guild"
		+" of the Spellweavers; you are not even a member!\n");
if ((this_player()->query_guild_name_occ()!=GUILD_NAME) 
		&&(this_player()->query_guild_name_lay()!=GUILD_NAME))
		return 0;

	if (
	   (   (this_player()->query_guild_name_occ()==GUILD_NAME)
		&& (this_player()->remove_guild_occ())      )
	   || ( (this_player()->query_guild_name_lay()==GUILD_NAME)
		 && (this_player()->remove_guild_lay())      )
								    )
	{
		write("As you withdraw your pledge to the"
			+" dark forces, you feel them leaving,"
			+" sapping your life force as they go.  Death descends"
			+" upon you as your honor shatters into dust.\n");
		say(QCTNAME(this_player())+ " has broken"
			+" the unholy pledge of the Spellweavers.  You"
			+" watch in horror as death descends to take"
			+" them away.\n");
		this_player()->set_hp(0);
		this_player()->do_die("Spellweaver withdrawal");
		
		TP->set_skill(SS_SPELLCRAFT, 0);
		TP->set_skill(SS_FORM_CONJURATION, 0);
		TP->set_skill(SS_FORM_DIVINATION, 0);
		TP->set_skill(SS_ELEMENT_DEATH, 0);
		TP->set_skill(SS_ELEMENT_EARTH, 0);
		TP->set_skill(SS_ELEMENT_AIR, 0);

	if ((this_player()->query_default_start_location())
			==(SWG+"startroom"))
		{
			if (this_player()->query_race_name()=="elf")
			this_player()->set_default_start_location("/d/Genesis/start/elf/room/begin");
			if (this_player()->query_race_name()=="dwarf")
			   this_player()->set_default_start_location("/d/Genesis/start/dwarf/lvl1/temple");
			if (this_player()->query_race_name()=="hobbit")
			   this_player()->set_default_start_location("/d/Genesis/start/hobbit/v/church");
			if (this_player()->query_race_name()=="goblin")
			   this_player()->set_default_start_location("/d/Genesis/start/goblin/caverns/quarters");
			if ((this_player()->query_race_name()=="human")
			    ||(this_player()->query_race_name()=="gnome"))
			   this_player()->set_default_start_location("/d/Genesis/start/human/town/church");
		}
				
	}

	else
		write("There was some error.  You were unable to withdraw"
			+"\n from the Spellweavers.  Please leave a note on"
			+"\n the bulletin board here in the guild, and"
			+"\n we will attempt to solve the problem.\n");
	return 1;
}

inviting(object invitee)
{
	object ob;
	notify_fail("You cannot invite a new member!  You are"
	+" not a Spellweaver!\n");
	if(!(this_player()->query_guild_member(GUILD_NAME)))
		return 0;

	notify_fail("Your candidate should be waiting outside"
		+" in the arrival chamber when you sponsor them from here.\n");
	ob = find_living(invitee);
	if (environment(ob) != (SWG+"arrive"))
		return 0;

	TP->catchmsg("You summon the power of the dark forces"
		+" to allow " + QNAME(ob) + " into the unholy shrine of the"
		+" Spellweavers.\n");
	ob->add_prop("_sw_i_am_invited_",1)
	ob->catch_msg(QCTNAME(TP) + " beckons to you to enter the unholy"
		+ " shrine.\n");

	return 1;
}

literature(string str)
{
	notify_fail("Read what?\n");

	if (str=="history")
	{
	write("\n"+"The Legend of the Spellweavers"+"\n\n"
		+ "In a time long past, far beyond the memory of"
		+" most, demons and the dark forces of night roamed,"
		+" and they were free, wreaking their havoc and delights"
		+" upon the world.  The forces of good, led by a group"
		+" of strange magic-users, took up their mystic arms and made"
		+" war on the demons.  The dark forces were taken by surprise,"
		+" and, after many decades of magical warfare, were"
		+" sealed behind mystic runes.\n\n"
		+"Now some could see the glorious power of the darkness,"
		+" and these turned away from the puny and pitiful ways of the light"
		+", the good, and tried to free the dark forces from their"
		+" confinement.  The good fought, but their best weakling"
		+" efforts only allowed the demons to remain"
		+" temporarily trapped behind their runes.  When the"
		+" evil ones formed the rune containing a specific demon, it was"
		+" released to come forth and serve that mortal.  Runes for"
		+" demons of servitude or protection were often sewn"
		+" into garments in the many days that followed, and"
		+" those with this talent became known as the Spellweavers.\n\n"
		+"In time, the good revolted, and the Spellweavers were"
		+" banished, destined to hide in caverns where the"
		+" blessed darkness protected them from the searching"
		+" eyes of the good.  Much of their lore and their craft"
		+" was lost, and of the thousands upon thousands of runes"
		+" once known, only a few remain.  The actual craft of"
		+" Spellweaving has passed away, but those now known"
		+" as the Spellweavers practice their craft simply by"
		+" the drawing of a rune upon the thin air before"
		+" them, and, though their might is diminished, the"
		+" dark forces return to serve.  The Spellweavers"
		+" continue to search for the lore lost in those many"
		+" long years of banishment; but for now, their power is"
		+" sufficient to at last step forth and challenge"
		+" the light that so long ago destroyed their"
		+" lifestyle and their craft.  The Spellweavers have "
		+" emerged!\n");
	return 1;
	}
    if(str == "rules")
	{
	write("\n"+"The Rules and Laws of the Spellweavers:\n"
		"1) You must serve the darkness. The demons will not tolerate serving one of " +
		"a good, king nature.\n" +
		"2) The secrets of the Spellweaver craft, and of the location of the entrance " +
		"to our guild and home shall remain hidden.  Let those who would join us seek " +
		"the entrance themselves, and show their worth.\n" +
		"3) You may join other guilds, as long as you maintain undying loyalty to the " +
		"Spellweavers.\n" +	
		"4) Due to our limited number, and the long years of hiding spent together, " +
		"the Spellweavers hold a special rapport amongst themselves; all "
		"Spellweavers shall at all times act to protect our own -- at any cost.\n" +
		"5) We shall seek vengeance for our own.  Any Spellweaver wronged shall be" +
		"avenged -- if necessary, by the guild as a whole.\n" +
		"6) The guild is ruled by the High Lord Magistrate of the Spellweavers. " +
		"The guildmaster is elected by the members of the guild. To help him in his " +
		"duties he appoints a Master Patterner and a Runemaster.\n" +
		"7) Members not meeting the standards of the Spellweavers, or those disclosing " +
		"the secrets of our unholy art to others, shall be expelled from out midst. " +
		"The High Lord Magistrate and his assistants have the power to expel members and " +
		"ban players from entering the guild.\n");
		"8) The penalty for leaving the servitude of the dark forces, by voluntary " +
		"withdrawal or by expulsion, is DEATH and a REMOVAL of your Spellweaver skills.\n" +
		"9) The demons shall serve, but they shall exact their price, taking 13% of " +
		"the layman's experience, and 30% of the full Spellweaver's.\n" +
		"10) You are welcomed into our ranks, to serve the might of the dark forces around " +
		"us.\n\n" +
		"          Sir Gunther, Immortal High Master of the Spellweavers\n");
		return 1;
	}
	return 0;
}

void
leave_inv(object ob, object to)
{
	::leave_inv(ob,to);
	gs_leave_inv(ob,to);
}

void
gs_hook_start_meditate()
{
	write("You kneel down here amidst the flickering torchlight"
	+" and concentrate on knowing yourself.  The dark forces in this room"
	+" swirl about you, lending their power to your efforts.  "
	+"You can <estimate> your level of stats and <set> those"
	+" rates at which each gets your attention, and the benefit of your"
	+" experience.  You may <rise> when finished.\n");
}

int
gs_hook_rise()
{
	write("You arise, coming back to your full consciousness.\n");
	say(QCTNAME(this_player())+" arises, having completed meditation.\n");
}

int
alter_membership()
{
    object shadow;
    int result;
    
    NF("You are not a member of the Spellweavers!!\n");
    if(!(TP->query_guild_member(GUILD_NAME))) 
	return 0;
	
	if(TP->query_guild_lay(GUILD_NAME))
    {
	NF("You are already an occupational member of another guild!\n");
	if(TP->query_guild_member_occ())
	    return 0;
	    
	shadow=clone_object(SHADOW_O);
	if (((result=shadow->shadow_me(this_player(),GTO,
	    GUILD_STYLE,GUILD_NAME))!=1))
	{
	    notify_fail("There is some error.  Please"
	        +" make a report to the Guildmasters of the"
		+" Spellweavers.\n");
	    "/secure/master"->do_debug("destroy",shadow);
	    return 0;
	}
	TP->remove_guild_lay();
	write("You alter your membership from layman"
	    +" Spellweaver to occupational.\n", 75));
	return 1;
    }
    else
    {
	NF("You are already a layman member of another guild!\n");
	if(TP->query_guild_member_lay()) 
	    return 0;
	    
	shadow=clone_object(SHADOW_L);
	if(((result=shadow->shadow_me(TP, GTL, GUILD_STYLE, GUILD_NAME))
	    !=1))
	{
	    NF("There is some error.  Please make a report"
		+" to the Guildmasters of the Spellweavers.\n");
	    "/secure/master"->do_debug("destroy", shadow);
	    return 0;
	}
	TP->remove_guild_occ();
	write("You alter your membership from occupational"
	    +" Spellweaver to layman.\n", 75));
	return 1;
    }
}
