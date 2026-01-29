
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/secure/std.h"
#include <ss_types.h>
#include "sw.h"

init()
{
	::init();
	add_action("ban_player","ban");
	add_action("expel_member","expel");
	add_action("appoint_asst","appoint");
	add_action("resign_position","resign");
	add_action("reaccept_banned_player","reaccept");
}

create_room()
{
	reset_euid();
	set_short("Guildmasters' Room");
	set_long("This is the private room of the"
		+" Guildmaster and Assistant Guildmasters"
		+" of the Spellweavers.  It is here that they can exercise their"
		+" great powers over the other guildmembers.  Here they"
		+" may <expel> any lower members.  They may <ban> any player from"
		+" entering the unholy guild home, or <reaccept> a previously"
		+" banned player.  The head Guildmaster may <appoint> a First or"
		+" Second Assistant Guildmaster (<appoint name first, appoint name"
		+" second>), while the First Assistant Guildmaster may"
		+" <appoint name second> a Second Assitant in the same manner.  If you"
		+" <appoint name none>, you will relieve that person of his/her/its"
		+" current position.  Finally,"
		+" any Guildmaster or Assistant Guildmaster may resign from"
		+" his/her/its position by using simply <resign>.  Please"
		+" note that players to be expelled, banned, etc. must"
		+" be in the world at the time the action is performed."
		+"  Please note also that all such actions ought to be affirmed"
		+" by the other Guildmasters, except in extreme circumstances."
		+"  Abuse of these powers will, of course, result in"
		+" demotion and possible expulsion from the ranks of"
		+" the Spellweavers."
		+"\n");

	add_exit(SWG+"priv_chapel","west",0);

	add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
}

int
resign_position()
{
	string *names;
	int n, m;
	
	names = allocate(3);
	n = query_bin_bits(0, 12, 13, TP);
	
	switch(n)
	{
	case SW_NORMAL :
	    write("You were never a Guildmaster of the Spellweavers\n"
			+"to begin with!\n");
	    return 0;
	case SW_GM_ASS2:
		write("You resign from the position of Second Assistant"
			+" Guildmaster,\n"
			+" Master Patterner of the Spellweavers.\n");
		break;
	case SW_GM_ASS1:
		write("You resign from the position of First Assistant"
			+" Guildmaster,\n"
			+" Runemaster of the Spellweavers.\n");
		break;
	case SW_GM:
		write("You resign from the position of Guildmaster,\n"
			+" Lord High Magistrate of the"
			+" Spellweavers.\n");
		break;
	}
			
	say(QCTNAME(TP)+" resigned.\n");
		
	for(m = 0; m < 3; m ++)
		if(m == n) names[m] = "none";
		else names[m] = read_file(GMFILE, m + 1, 1);
	rm(GMFILE);
	for(m = 0; m < 3; m++)
		write_file(GMFILE, names[m]+"\n");

	set_bin_bits(0, 12, 13, TP, 0); /* Always step down completely */
	
}

int
ban_player(string who)
{
	object ob;
	int n;

	NF("Only Guildmasters of the Spellweavers can do that!\n");
	n = query_bin_bits(0, 12, 13, TP);
	if(n == 0 && !(SECURITY->query_wiz_level(TP->query_real_name())&&
                (TP->query_guild_member(GUILD_NAME))) return 0;
    /* mortal gms and wiz members can ban */

	NF("Ban whom from entering the guild?\n");
	if(!strlen(who)) return 0;
		
	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob=find_player(who))) return 0;
		
	NF("That player is already banned from entering the guild.\n");
	if(ob->test_bit("Rhovanion", 0, 11)) return 0;
		
	write("You ban "+who+" from entering the guild.\n");
	ob->set_bit(0,11);
	return 1;	
}

int
expel_member(string who)
{
    object ob;

    NF("Only Guildmasters can do that!\n");
	n = query_bin_bits(0, 12, 13, TP);
	if(n == 0 && !(SECURITY->query_wiz_level(TP->query_real_name())&&
                (TP->query_guild_member(GUILD_NAME))) return 0;
    /* mortal gms and wiz members can expel */
	NF("Expel whom from the guild?\n");
	if(!strlen(who)) return 0;

	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob=find_player(who))) return 0;

	NF("That player is not a member of the Spellweavers!\n");
	if(!(ob->query_guild_member(GUILD_NAME))) return 0;
	
	/* See if the member to be expelled is a GM-- if so, they must
	* retire or be fired first.
	*/
	NF("That player is a Guildmaster and must retire or be fired"
	+" before being expelled.\n");
	
	if(n > 0) return 0;
	
	TP->catch_msg("You expel "+QCNAME(ob)+" from the Spellweavers' guild.\n");
	ob->catch_msg(QCTNAME(TP)+" has expelled you from the ranks of"
	+" the Spellweavers!\n");
	
	/* Death */
	ob->set_hp(0);
	ob->do_die("Spellweaver expulsion");
	
	/* Remove guild shadow/soul*/
	if(TP->query_guild_occ(GUILD_NAME))
		TP->remove_guild_occ();
	else
		TP->remove_guild_lay();
	
	/* Removal of skills */
	ob->set_skill(SS_SPELLCRAFT, 0);
	ob->set_skill(SS_FORM_CONJURATION, 0);
	ob->set_skill(SS_FORM_DIVINATION, 0);
	ob->set_skill(SS_ELEMENT_DEATH, 0);
	ob->set_skill(SS_ELEMENT_EARTH, 0);
	ob->set_skill(SS_ELEMENT_AIR, 0);
	
	/* Reset start location if you start here */
	if ((ob->query_default_start_location()) == (SWG+"startroom"))
	{
		if (ob->query_race_name()=="elf")
		ob->set_default_start_location("/d/Genesis/start/elf/room/begin");
		if (ob->query_race_name()=="dwarf")
		ob->set_default_start_location("/d/Genesis/start/dwarf/lvl1/temple");
		if (ob->query_race_name()=="hobbit")
		ob->set_default_start_location("/d/Genesis/start/hobbit/v/church");
		if (ob->query_race_name()=="goblin")
		ob->set_default_start_location("/d/Genesis/start/goblin/caverns/quarters");
		if ((ob->query_race_name()=="human") ||(ob->query_race_name()=="gnome"))
		ob->set_default_start_location("/d/Genesis/start/human/town/church");
	}
	return 1;
}

int
reaccept_banned_player(string who)
{
    object ob;
  
    NF("Only Guildmasters can do that!\n");
	n = query_bin_bits(0, 12, 13, TP);
	if(n == 0 && !(SECURITY->query_wiz_level(TP->query_real_name())&&
                (TP->query_guild_member(GUILD_NAME))) return 0;
    /* mortal gms and wiz members can reaccept */
	
	NF("Reaccept what banned player?\n");
	if(!strlen(who))
	    return 0;
	    
	NF("That player does not exist or is not currently in the game.\n");
	if(!(ob=find_player(who))) 
	    return 0;
	
	NF("That player was never banned!\n");
    if(!(ob->test_bit("Rhovanion",0,11)))
	    return 0;
	    
	TP->catch_msg("You remove the ban on "+QCNAME(ob)+".\n");
	
	ob->catch_msg(QCTNAME(TP)+" has released the Spellweavers'"
	    +" ban on you.\n");
	ob->clear_bit(0, 11);
	
	return 1;
    }
}

int
appoint_asst(string arg)
{
    object ob;
    string *stuff;
    string *gms;
    string number, name;
    int rank, obrank, n, m;
    
    stuff=explode(arg, " ");
    name=stuff[0];
    number=stuff[1];
    gms = allocate(3);
    
    NF("Appoint whom to what Assistant Guildmaster position?\n");
    if((!strlen(name))||(!strlen(number)))
	return 0;
	
    NF("That player does not exist or is not currently in the game.\n");
    if(!(ob=find_player(name)))
	return 0;
	
    NF("That player is already a Guildmaster.  "+CAP(HE(ob))
	+" must resign or be removed before being reassigned to a new"
	+" position.\n");
	
	rank = query_bin_bits(0, 12, 13, TP);
	if(rank > 0 && number != "none") return 0;
	
    NF("That player is not a Spellweaver!\n");
    if(!(ob->query_guild_member(GUILD_NAME)))
	return 0;

	obrank = query_bin_bits(0, 12, 13, ob);

    if(number="none")
    {
    	string title;
		/* Test to see if TP has the authority to fire ob */
		                                                 
		if(!obrank) /* ob wasn't a guildmaster */
		{
		    write("You've chosen to remove someone who is not a Guildmaster!\n"); 
		    return 0;
        }
        
        NF("You do not have the authority to remove " + CAP(ME(ob)) + ".\n");
		if(! (rank > obrank || (TP->query_guild_member(GUILD_NAME)
			&& SECURITY->query_wiz_level(TP->query_real_name())))) return 0;

		/* Ok, lets demote */
		title = (obrank == 2)?"First":"Second";
		TP->catch_msg("You remove " + QCNAME(ob) + " as " + title +
				" Assistant Guildmaster of the Spellweavers.\n");
		ob->catch_msg(QCTNAME(TP) + " has removed you from the position"
			+ " of " + title + " Assistant Guildmaster of the Spellweavers.\n");
		
		for(n = 0; n < 3; n++) gms[n] = read_file(GMFILE, n + 1, 1);
		rm(GMFILE);
		gms[obrank - 1] = "none";
		for(n = 0; n < 3; n++) write_file(GMFILE, gms[n] + "\n");
		set_bin_bits(0, 12, 13, ob, 0); /* clear the bits */
		return 1;
    }

	NF("You lack the authority to promote anyone.\n");	
	if(! (rank > SW_GM_ASS2) || (TP->query_guild_member(GUILD_NAME)
		&& SECURITY->query_wiz_level(TP->query_real_name())))) return 0;

    n = 0;
    NF("Promote that player to what position?"
    if(number == "second") n = 1;
    if(number == "first") n = 2;
    if(!n) return 0;
    
    NF("You cannot promote anyone to your own position.\n");
    if(rank == n) return 0; /* only applies to first assistant really */
	
	NF("That person already holds that position!\n");
	if(n == obrank) return 0;
	
	NF("That person already holds another position!\n");
	if(obrank) return 0;
	                                     
	NF("Someone else already holds that position!\n");	                                     
	if(read_file(GMFILE, n, 1) != "none") return 0;
	    
	/* ok, promote */
	set_bin_bits(0, 12, 13, ob, n);
	obrank = n;
	
	for(m = 0; m < 3; m++) gms[m] = read_file(GMFILE, m + 1, 1);
	rm(GMFILE);
	gms[n - 1] = "none";
	for(n = 0; n < 3; n++) write_file(GMFILE, gms[n] + "\n");
	title = (obrank == 2)?"First":"Second";
	TP->catch_msg("You appointed " + QCNAME(ob) + " to the position of "
		+ title + " Assistant Guildmaster of the Spellweavers.\n");
	ob->catch_msg(QCTNAME(TP) + " appointed you to the position of "
		+ title + " Assistant Guildmaster of the Spellweavers.\n");
	tell_room(environment(), QCTNAME(TP) + " appointed " + QCNAME(ob) +
		" to the position of " + title + " Assistant Guildmaster of"
		+ " the Spellweavers.\n");
}
